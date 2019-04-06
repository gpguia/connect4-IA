#ifndef MCTS_H
#define MCTS_H

#include "board.h"
#include <cmath>
#include <time.h>

#define MP make_pair
#define TIME_LIMIT 2000000

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
    for(int i=0;i<7;i++){
      children.push_back(NULL);
    }
  }

};

class MCTS{
private:
  node *root;
  void clear(node *n);
  double eval(node *n, int num);
  node *select(node *root);
  node *expand(node *n);
  int simulate(node *n);
  void backpropagate(node *n, int win);
  node *rSelection();
public:
  MCTS();
  virtual ~MCTS();
  int mcts(Board *b);

};

#endif
