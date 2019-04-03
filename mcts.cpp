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
  int res=-1;
  node *clone1,clone2;
  while(clock() - start_time < time_limit){
    clone1 = b->clone();
    n = select(root,clone1);
    if(n == NULL){
      continue;
    }
    clone2 = clone1->clone();

    expand(n,clone1);
    res = simulate(clone1);
    backpropagate(clone1,res);
  }
  int bestResultNode=-1;
  for(int i=0;i<7;i++){
    if(root->children[i] != NULL){
      if(bestResultNode == -1 || root->children[i]->games > root->children[bestResultNode]->games){
        bestResultNode=i;
      }
    }
  }

  return bestResultNode;
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

node *MCTS::expand(node *n,Board *b){
  vector<int> arrToVisit;
  for(int i=0;i<7;i++){
    if(n->children[i] == NULL && n->board->isColumnFree(i)){
      arrToVisit.push_back(i);
    }
  }
  int randNum = rand() % arrToVisit.size();
  int k = arrToVisit[randNum];
  Board *b3 = n->board->clone();
  b3->playMCTS(k);
  n->children[k] = new node(n,b3);
  return n->children[k];
}

int MCTS::simulate(Board *b){
  int randCol=0;
  Board *b2 = b->clone();

  int countPossibleMoves=0;
  for(int i=0;i<7;i++){
    if(b->getBoard().at(0).at(i) == '-'){
      countPossibleMoves++;
    }
  }

  while(b2->isGameOver()){
    randCol = rand() % countPossibleMoves;
    int row = b2->getRow(randCol);
    b2->playMCTS(randCol);
    int win = b2->checkWin(row,randCol);
    if(win == 1){
      return 1; //AI WON
    }else if(win == 0){
      return 0; //PLAYER WON
    }
  }
  return -1; //draw
}

void MCTS::backpropagate(node *n, int win){
  node *cur = n;
  while(cur != NULL){
    cur->games++;
    cur->wins+=win;
    cur = cur->parent;
  }
}
