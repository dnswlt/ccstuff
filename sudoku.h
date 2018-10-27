#ifndef CC_SUDOKU_H_
#define CC_SUDOKU_H_

#include <bitset>
#include <vector>

int Ind(int r, int c, int num);

class Move {
public:
  int r;
  int c;
  int num;
  std::bitset<9*9*9> mask;
  Move(int r, int c, int num);
};


class State {
public:
  State(const Move *move) : move_(move), mask(move->mask) {
  }
  State(const State& pred, const Move *move) : move_(move), mask(pred.mask | move->mask) {
  } 
  bool Possible(int r, int c, int num) const;
  const Move *move() const { return move_; }
private:
  std::bitset<9*9*9> mask;
  const Move *move_;
};

class Board {
public:
  int backtrack_cnt = 0;
  std::vector<const Move*> all_moves;
  std::vector<State> states;
  int nums[9][9];
  Board();
  ~Board();
  void MakeMove(int r, int c, int num);
  bool Solve();
private:
  const Move* GetMove(int r, int c, int num);
  void MakeMove(const Move *m);
  const State& Current();
  std::vector<const Move*> NextMoves();
  void Backtrack();
  bool Done();
};

std::ostream &operator<<(std::ostream& os, const Board& board);

 
#endif // CC_SUDOKU_H_

