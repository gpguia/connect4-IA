#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "board.h"
#include <queue>
#include <ctime>
#include <cstdlib>

class Alphabeta{
private:
public:
  Alphabeta();
  virtual ~Alphabeta();
  int alphabeta(Board *b, int alpha, int beta, int depth);
  int max_value(Board b, int alpha, int beta, int depth, int limit);
  int min_value(Board b, int alpha, int beta, int depth, int limit);
  queue <Board> children(Board *b, char turn);
};


#endif
