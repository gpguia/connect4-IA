#include "mcts.h"


MCTS::MCTS(){

}

MCTS::~MCTS(){

}

int MCTS::mcts(Board *b){
  startTree(b,'O');
  return 0;
}

void MCTS::startTree(Board *b, char turn){
  Board child;
  int row;
  for(int col=0;col<7;col++){
    if(b->getBoard().at(0).at(col) == '-'){ //verify if is playable
      child = *b;
      row = child.getRow(col);
      child.setPos(row,col,turn);
      tree[col].insert(MP(MP(0,0),child));
    }
  }
}
