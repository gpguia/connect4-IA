#include "mcts.h"


MCTS::MCTS(){

}

MCTS::~MCTS(){

}

int MCTS::mcts(Board *b, int time_limit){
  int start_time = clock();
  srand(time(NULL));

  node *root = new node(NULL,b);
  node *n, *child;
  Board *clone1,*clone2;
  int res=-1;

  while(clock() - start_time < time_limit){
    clone1 = b->clone();
    n = select(root,clone1);
    clone2 = clone1->clone();

    expand(n,clone1);
    res = simulate(clone2,b->getTurn(),42);

  }

  return 0;
}

double MCTS::eval(node *n, int num){
  if(!n->hasChildren()){
    return 0.5 + EXPLOR_PARAM*sqrt(log(num+1));
  }
  double weight = n->wins/((double)n->games+1);
  if('O' != n->board->getTurn())
    weight = 1.0-weight;
  return weight + EXPLOR_PARAM*sqrt(log(num+1)/((double)n->games+1));
}

int MCTS::select_child(node *n){
  int childSize = (int)n->children.size();
  int bestMove = 0;
  double value = -1,val;
  for(int i=0; i<7;i++){
    val = eval(n->children[i],n->games);
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

  int best = select_child(root);

  return select(root->children[best],b);

}

void MCTS::expand(node *n,Board *b){

  for(int j=0;j<7;j++){
    if(n->board->getBoard().at(0).at(j) != '-'){
      n->children.push_back(new node(n,b));
    }
  }
}

int MCTS::simulate(Board *b, char turn, int depth_max){
  int countPossibleMoves=0;
  int end = b->isGameOver();
  if(end)
    return end;

  if(!depth_max) return 0;

  for(int i=0;i<7;i++){
    if(b->getBoard().at(0).at(i) == '-'){
      countPossibleMoves++;
    }
  }

  int r = rand() % countPossibleMoves;
  b->playMCTS(r);

  return simulate(b,b->getTurn(),depth_max-1);
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
