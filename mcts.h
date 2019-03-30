#ifndef MCTS_H
#define MCTS_H

#include "board.h"
#include <cmath>

#define MP make_pair


const double EXPLOR_PARAM = 1.3;

struct node{
  node *parent;
  int games;
  int wins;
  char turn;

  vector<node*> children;

  node(node *n, char t){
    parent = n;
    turn = t;
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
  double eval(node *n, int num, char turn);
  int select_child(node *n, char turn);
  node *select(node *root, Board *b);
public:
  MCTS();
  virtual ~MCTS();
  int mcts(Board *b);

};

#endif
