#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include <queue>
#include <ctime>
#include <cstdlib>

class Minimax{
private:
  int pts[4];
  queue <Board> children(Board *b, char turn);
  int max_value(Board b, int depth, int limit);
  int min_value(Board b, int depth, int limit);
public:
  Minimax();
  virtual ~Minimax();
  int minimax(Board *b, int depth);
};

#endif
