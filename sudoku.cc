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
  Move(int r, int c, int num) : r(r), c(c), num(num) {
    for (int i=0; i<9; i++) {
      mask[Ind(r, i, num)] = true;
      mask[Ind(i, c, num)] = true;
    }
    int br = r / 3;
    int bc = c / 3;
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
        mask[Ind(br+i, bc+j, num)] = true;
      }
    }
  }
};

class State {
public:
  std::bitset<9*9*9> mask;
  State(const Move *move) : mask{} {
    mask |= move->mask;
  }
  State(const State& pred, const Move *move) {
    mask = pred.mask | move->mask;
  } 
};

class Board {
public:
  std::vector<const Move*> moves;
  std::vector<State> states;
  std::vector<const Move*> made_moves;
  Board() : moves(9*9*9) {
    int idx = 0;
    for (int i=0; i<9; i++) {
      for (int j=0; j<9; j++) {
        for (int n=1; n<=9; n++) {
          moves[idx] = new Move(i, j, n);
          idx++;
        }
      }
    }
  }
  ~Board() {
    for (auto const m : moves) {
      delete m;
    }
    std::cout << "Board deleted\n";
  }
  void MakeMove(const Move *m) {
    made_moves.push_back(m);
    if (states.size() == 0) {
      states.push_back(State(m));
    } else {
      states.push_back(State(states[states.size()-1], m));
    }
  }
  void Backtrack() {
    states.pop_back();
    made_moves.pop_back();
  }
  const Move* GetMove(int r, int c, int num) {
    return moves[r * 81 + c * 9 + num];
  }
  bool Done() {
    return states.size() == 81;
  }
  const State& Current() {
    return states[states.size()-1];
  }
  int EvalMove(const Move *m) {
    if (Current().mask[Ind(m->r, m->c, m->num)]) {
      return -1;
    }
    int choices = 0;
    for (int n=1; n<=9; n++) {
      if (!Current().mask[Ind(m->r, m->c, n)]) {
        choices++;
      }
    }
    return choices;
  }
};


bool Solve(Board& board) {
  if (board.Done()) {
    return true;
  }
  const State& s = board.Current();
  std::vector<const Move*> next_moves;
  std::vector<int> values;
  for (auto const m : board.moves) {
    int v = board.EvalMove(m);
    if (v > 0) {
      next_moves.push_back(m);
      values.push_back(v);
    }
  }
  int value = 1;
  while (value <= 9) {
    for (int i=0; i<next_moves.size(); i++) { 
      if (values[i] == value) {
        board.MakeMove(next_moves[i]);
        bool solved = Solve(board);
        if (solved) {
          return true;
        }
        board.Backtrack();
      }
    }
    ++value;
  }
  return false;
}

std::ostream &operator<<(std::ostream& os, const Board& board) {
  int b[9][9] = {};
  for (auto const m : board.made_moves) {
    b[m->r][m->c] = m->num;
  }
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
  std::cout << board.states.size() << " moves read\n";
  std::cout << board << "\n";
  bool solved = Solve(board);
  if (solved) {
    std::cout << "Board solved\n";
    std::cout << board;
  } else {
    std::cout << "Board unsolved\n";
  }
}


