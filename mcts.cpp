#include "mcts.h"


MCTS::MCTS(){

}

MCTS::~MCTS(){

}

int MCTS::mcts(Board *b){
  startTree(b,'O');
  return 0;
}
