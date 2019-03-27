#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "board.h"
#include <queue>
#include <ctime>
#include <cstdlib>

class Alphabeta{
private:
  int pts[4];
public:
  Alphabeta();
  virtual ~Alphabeta();
  int alphabeta(Board *b, int alpha, int beta, int depth);
  int max_value(Board b, int alpha, int beta, int depth, int limit);
  int min_value(Board b, int alpha, int beta, int depth, int limit);
  int checkPoints(Board b, int row, int col, char turn);
  int utility(Board b);
  int calcHor(Board b, int row, int col, char turn);
  int calcVert(Board b, int row, int col, char turn);
  int calcDig(Board b, int row, int col, char turn);
  int calcRDig(Board b, int row, int col, char turn);
  queue <Board> children(Board *b, char turn);
};


#endif
