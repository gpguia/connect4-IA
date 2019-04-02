#include "mcts.h"


MCTS::MCTS(){

}

MCTS::~MCTS(){

}

int MCTS::mcts(Board *b){
  node *root = new node(NULL,b->getTurn());
  node *n, *child;
  Board *clone1,*clone2;
  int res;

  while(1){
    clone1 = b->clone();
    n = select(root,clone1);
    clone2 = clone1->clone();

    expand(n,clone1);
    res = simulate(clone2,n->turn,120);

  }

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

void MCTS::expand(node *n, Board *b){

}

int MCTS::simulate(Board *b, char turn, int depth_max){
  int end = b->isGameOver();
  if(end)
    return end;

  if(!depth_max) return 0;

  int r = rand() % 7;
  b->playMCTS(r);

  if(turn == 'X'){
    return simulate(b,'O',depth_max-1);
  }
  return simulate(b,'X',depth_max-1);
}

void MCTS::backpropagate(node *n, int win, char turn){
  if(!n->parent) return;

  if(win == 1 || turn == 'X')
    n->wins+=win;

  n->games+=2;

  if(turn == 'X'){
    backpropagate(n->parent,win,'O');
  }
  backpropagate(n->parent,win,'X');
}
