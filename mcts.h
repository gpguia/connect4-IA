#ifndef MCTS_H
#define MCTS_H

#include "board.h"
#include <cmath>
#include <map>

#define TREE map<pair<int,int>,Board>
#define MP make_pair

class MCTS{
private:
  TREE tree[7]; //create a vector of map for the childs.
public:
  MCTS();
  virtual ~MCTS();
  int mcts(Board *b);

  void startTree(Board *b, char turn);
  pair<int,int> selection();
};

#endif
