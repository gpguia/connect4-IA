#include "mcts.h"


MCTS::MCTS(){

}

MCTS::~MCTS(){

}

int MCTS::mcts(Board *b){

  return 0;
}

double MCTS::eval(node *n, int num, char turn){
  if(!n->hasChildren()){
    return 0.5 + EXPLOR_PARAM*sqrt(log(num+1));
  }
  double weight = n->wins/((double)n->games+1);
  if(turn != n->turn)
    weight = 1.0-weight;
  return weight + EXPLOR_PARAM*sqrt(log(num+1)/((double)n->games+1));
}

int MCTS::select_child(node *n, char turn){
  int childSize = (int)n->children.size();
  int bestMove = 0;
  double value = -1,val;
  for(int i=0; i<7;i++){
    val = eval(n->children[i],n->games,turn);
    if(val > value){
      value = val;
      bestMove = i;
    }
  }
  return bestMove;
}

node *MCTS::select(node *root, Board *b){
  if(!root){
    cout << "Error: root NULL" << endl;
    exit(1);
  }
  if(!root->hasChildren())
    return root;

  int best = select_child(root,b->getTurn());

  return select(root->children[best],b);
}
