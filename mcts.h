#ifndef MCTS_H
#define MCTS_H

#include "board.h"
#include <cmath>
#include <time.h>

#define MP make_pair


const double EXPLOR_PARAM = 1.3;

struct node{
  node *parent;
  int games;
  int wins;
  Board *board;

  vector<node*> children;

  node(node *n, Board *b){
    board = b;
    parent = n;
    games=0;
    wins=0;
  }

  bool hasChildren(){
    return !children.empty();
  }
};

class MCTS{
private:
  void clear(node *n);
  double eval(node *n, int num);
  int select_child(node *n);
  node *select(node *root, Board *b);
  void expand(node *n, Board *b);
  int simulate(Board *b, char turn, int depth_max);
  void backpropagate(node *n, int win, char turn);
public:
  MCTS();
  virtual ~MCTS();
  int mcts(Board *b, int time_limit);

};

#endif
