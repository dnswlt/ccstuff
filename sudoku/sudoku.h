#ifndef CCSTUFF_SUDOKU_H_
#define CCSTUFF_SUDOKU_H_

#include <bitset>
#include <vector>

// Type definitions and util functions of the sudoku solver.


// Move represents a single "move" in Sudoku, i.e. writing down a number
// on a particular field of the Sudoku board. Each move has an associated
// `mask` that has all bits of positions set that are mutually exclusive 
// with this move set.
class Move {
public:
  int r;
  int c;
  int num;
  std::bitset<9*9*9> mask;
  Move(int r, int c, int num);
};


// State represents the possible remaining moves.
class State {
public:
  State(const Move *move) : move_(move), mask(move->mask) { }
  State(const State& pred, const Move *move) : move_(move), mask(pred.mask | move->mask) { } 
  bool Possible(int r, int c, int num) const;
  const Move *move() const { return move_; }
private:
  std::bitset<9*9*9> mask;
  const Move *move_;
};


// Board represents an ongoing or finished Sudoku game and solves incomplete games.
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

// Allows to send the current board contents to an ostream.
std::ostream &operator<<(std::ostream& os, const Board& board);

 
#endif // CCSTUFF_SUDOKU_H_

