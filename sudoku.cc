#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <bitset>

int Ind(int r, int c, int num) {
  return r * 81 + c * 9 + (num-1);
}

class Move {
public:
  int r;
  int c;
  int num;
  std::bitset<9*9*9> mask;
  Move(int r, int c, int num) : r(r), c(c), num(num), mask{} {
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
};

class State {
  std::bitset<9*9*9> mask;
  const Move *move_;
public:
  State(const Move *move) : move_(move), mask(move->mask) {
  }
  State(const State& pred, const Move *move) : move_(move), mask(pred.mask | move->mask) {
  } 
  bool Possible(int r, int c, int num) const {
    return !mask.test(Ind(r, c, num));
  }
  const Move *move() const { return move_; }
};

class Board {
public:
  int backtrack_cnt = 0;
  std::vector<const Move*> all_moves;
  std::vector<State> states;
  int nums[9][9];
  Board() : all_moves(9*9*9), nums{} {
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
  ~Board() {
    for (auto const m : all_moves) {
      delete m;
    }
    std::cout << "Board deleted\n";
  }
  void MakeMove(const Move *m) {
    nums[m->r][m->c] = m->num;
    if (states.size() == 0) {
      states.push_back(State(m));
    } else {
      states.push_back(State(states[states.size()-1], m));
    }
  }
  void Backtrack() {
    auto const m = Current().move();
    states.pop_back();
    nums[m->r][m->c] = 0;
    backtrack_cnt++;
  }
  const Move* GetMove(int r, int c, int num) {
    return all_moves[Ind(r, c, num)];
  }
  bool Done() {
    return states.size() == 81;
  }
  const State& Current() {
    return states[states.size()-1];
  }
  std::vector<const Move*> NextMoves() {
    if (states.size() == 0) {
      return std::vector<const Move*>({all_moves[0]});
    }
    int ps[9][9] = {};
    for (auto const m : all_moves) {
      if (nums[m->r][m->c] == 0 && Current().Possible(m->r, m->c, m->num)) {
        ps[m->r][m->c]++;
      }
    }
    int min_i = -1;
    int min_j = 0;
    for (int i=0; i<9; i++) {
      for (int j=0; j<9; j++) {
        if (nums[i][j] > 0) {
          // already assigned
          continue;
        } else if (ps[i][j] == 0) {
          // no possible choices: time to backtrack
          return std::vector<const Move*>();  
        } else if (min_i == -1 || ps[i][j] < ps[min_i][min_j]) {
          min_i = i;
          min_j = j;
        }
      }
    }
    std::vector<const Move*> result;
    for (int n=1; n<=9; n++) {
      const Move *m = GetMove(min_i, min_j, n);
      if (Current().Possible(m->r, m->c, m->num)) {
        result.push_back(m);
      }
    }
    return result;
  }
};


bool Solve(Board& board) {
  if (board.Done()) {
    return true;
  }
  for (auto const m : board.NextMoves()) {
    board.MakeMove(m);
    bool solved = Solve(board);
    if (solved) {
      return true;
    }
    board.Backtrack();
  }
  return false;
}

std::ostream &operator<<(std::ostream& os, const Board& board) {
  auto b = board.nums;
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (b[i][j] > 0) {
        os << b[i][j];
      } else {
        os << " ";
      }
    }
    os << "\n";
  }
  return os;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <board-file>\n";
    return 1;
  }  
  std::ifstream f_in(argv[1]);
  if (!f_in) {
    std::cout << "Could not open file " << argv[1] << "\n";
    return 1;
  }
  Board board;
  int row = 0;
  for (std::string line; std::getline(f_in, line); ) {
    if (line.length() == 0) {
      continue;
    }
    if (line.length() != 9) {
      std::cout << "Invalid line: " << line << "\n";
      return 1;
    }
    for (int i=0; i<9; i++) {
      if (std::isdigit(line[i])) {
        int n = line[i] - '0';
        board.MakeMove(board.GetMove(row, i, n));
      }
    }
    row++;
  } 
  std::cout << "Board with " << board.states.size() << " numbers read\n";
  std::cout << board << "\n";
  bool solved = Solve(board);
  if (solved) {
    std::cout << "Board solved, backtracked " << board.backtrack_cnt << " times\n";
    std::cout << board;
  } else {
    std::cout << "Board unsolved\n";
  }
}


