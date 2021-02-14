#include "sudoku.h"

#include <bitset>
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <string_view>
#include <vector>

static int Ind(int r, int c, int num) {
  return r * 81 + c * 9 + (num-1);
}

Move::Move(int r, int c, int num) : r(r), c(c), num(num), mask{} {
  for (int i=0; i<9; i++) {
    mask[Ind(r, i, num)] = true;
    mask[Ind(i, c, num)] = true;
  }
  int br = r / 3;
  int bc = c / 3;
  for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++) {
      mask[Ind(br*3+i, bc*3+j, num)] = true;
    }
  }
}

bool State::Possible(int r, int c, int num) const {
  return !mask.test(Ind(r, c, num));
}

Board::Board() : all_moves(9*9*9), nums{} {
  int idx = 0;
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      for (int n=1; n<=9; n++) {
        all_moves[idx] = new Move(i, j, n);
        idx++;
      }
    }
  }
}

Board::~Board() {
  for (auto const m : all_moves) {
    delete m;
  }
  std::cout << "Board deleted\n";
}

void Board::MakeMove(const Move *m) {
  nums[m->r][m->c] = m->num;
  if (states.size() == 0) {
    states.push_back(State(m));
  } else {
    states.push_back(State(states[states.size()-1], m));
  }
}

void Board::Backtrack() {
  auto const m = Current().move();
  states.pop_back();
  nums[m->r][m->c] = 0;
  backtrack_cnt++;
}

const Move* Board::GetMove(int r, int c, int num) {
  return all_moves[Ind(r, c, num)];
}

void Board::MakeMove(int r, int c, int num) {
  MakeMove(GetMove(r, c, num));
}

bool Board::Done() {
  return states.size() == 81;
}

const State& Board::Current() {
  return states[states.size()-1];
}

// Computes all possible next moves of the square that is most constrained,
// i.e. allows the least amount of numbers to be tried. If this square is not
// unique, returns moves for an arbitrary such square.
std::vector<const Move*> Board::NextMoves() {
  if (states.size() == 0) {
    // Nothing on the board yet, any move should work
    return std::vector<const Move*>({all_moves[0]});
  }
  // For each square, count the remaining choices
  int choices[9][9] = {};
  for (auto const m : all_moves) {
    if (nums[m->r][m->c] == 0 && Current().Possible(m->r, m->c, m->num)) {
      choices[m->r][m->c]++;
    }
  }
  // Find square with minimum choices left
  int min_i = -1;
  int min_j = 0;
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (nums[i][j] > 0) {
        // already assigned
        continue;
      } else if (choices[i][j] == 0) {
        // no possible choices: board is in invalid state. Time to backtrack.
        return std::vector<const Move*>();  
      } else if (min_i == -1 || choices[i][j] < choices[min_i][min_j]) {
        min_i = i;
        min_j = j;
      }
    }
  }
  // Collect possible moves for min square
  std::vector<const Move*> result;
  for (int n=1; n<=9; n++) {
    const Move *m = GetMove(min_i, min_j, n);
    if (Current().Possible(m->r, m->c, m->num)) {
      result.push_back(m);
    }
  }
  return result;
}

// Local search with backtracking
bool Board::Solve() {
  if (Done()) {
    return true;
  }
  for (auto const m : NextMoves()) {
    MakeMove(m);
    bool solved = Solve();
    if (solved) {
      return true;
    }
    Backtrack();
  }
  return false;
}

std::ostream &operator<<(std::ostream& os, const Board& board) {
  auto b = board.nums;
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (b[i][j] > 0) {
        os << b[i][j] << " ";
      } else {
        os << ". ";
      }
    }
    os << "\n";
  }
  return os;
}

bool ReadFromFile(std::string_view filename, Board& board) {
  std::ifstream f_in(filename);
  if (!f_in) {
    std::cout << "Could not open file " << filename << "\n";
    return false;
  }
  int row = 0;
  for (std::string line; std::getline(f_in, line); ) {
    if (line.length() == 0) {
      continue;
    }
    if (line.length() != 9) {
      std::cout << "Invalid line: " << line << "\n";
      return false;
    }
    for (int i=0; i<9; i++) {
      if (std::isdigit(line[i])) {
        int n = line[i] - '0';
        board.MakeMove(row, i, n);
      }
    }
    row++;
  } 
  std::cout << "Board with " << board.states.size() << " numbers read\n";
  return true;
}

bool ReadFromString(std::string_view board_values, Board& board) {
  std::regex board_regex(R"re([0-9. ]+)re");
  if (board_values.size() != 81 || 
      !std::regex_match(board_values, board_regex)) {
    return false;
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      char c = board_values[i * 9 + j];
      if (std::isdigit(c)) {
        board.MakeMove(i, j, c - '0');
      }
    }
  }
  return true;
}

// Read board from a text file, and solve it
int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <board-file|board-string>\n";
    return 1;
  }  
  Board board;
  if (!ReadFromString(argv[1], board) &&
      !ReadFromFile(argv[1], board)) {
    std::cout << "Cannot build board from " << argv[1] << "\n";
    return 1;
  }
  std::cout << board << "\n";
  bool solved = board.Solve();
  if (solved) {
    std::cout << "Board solved, backtracked " << board.backtrack_cnt << " times\n";
    std::cout << board;
  } else {
    std::cout << "Board unsolved\n";
  }
}


