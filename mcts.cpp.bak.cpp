#include "mcts.h"


MCTS::MCTS(){

}

MCTS::~MCTS(){

}

int MCTS::mcts(Board *b){
  clock_t start_time = clock();
  this->root = new node(NULL,b);
  int res=-1;

  while(clock() - start_time < TIME_LIMIT){
    node *n = rSelection();
    if(n == NULL){
      continue;
    }

    node *child = expand(n);
    res = simulate(child);
    backpropagate(child,res);
  }
  int bestResultNode=-1;
  for(int i=0;i<7;i++){
    if(root->children[i] != NULL){
      if(bestResultNode == -1 || root->children[i]->games > root->children[bestResultNode]->games){
        bestResultNode=i;
      }
    }
  }
  cout << "ret: " << bestResultNode << endl;
  return bestResultNode;
}

node *MCTS::rSelection(){
  return select(this->root);
}

node *MCTS::select(node *parent){
  for(int i=0;i<7;i++){
    if(parent->children[i] == NULL && !parent->board->isColumnFree(i)){
      return parent;
    }
  }
  double maxVal = -1;
  int maxIndex = -1;
  for(int i=0;i<7;i++){
    if(parent->board->isColumnFree(i))
      continue;

    node *cur = parent->children[i];
    double wins;
    if(parent->board->getTurn() == 'X'){
      wins = (double)cur->wins;
    }else{
      wins = (double)(cur->games - cur->wins);
    }
    double val = (wins/cur->games) + sqrt(2)*sqrt(log(parent->games)/cur->games);
    if(val > maxVal){
      maxVal = val;
      maxIndex = i;
    }
  }
  if(maxVal == -1)
    return NULL;
  return select(parent->children[maxIndex]);
}

node *MCTS::expand(node *n){
  srand(time(NULL));
  vector<int> arrToVisit;
  for(int i=0;i<7;i++){
    if(n->children[i] == NULL && !n->board->isColumnFree(i)){
      arrToVisit.push_back(i);
    }
  }
  int randNum = rand() % (int)arrToVisit.size();
  int k = arrToVisit[randNum];
  Board *b3 = n->board->dup();
  b3->playMCTS(k);
  n->children[k] = new node(n,b3);
  return n->children[k];
}

int MCTS::simulate(node *n){
  srand(time(NULL));
  int randCol=0;
  Board *b2 = n->board->dup();
  int countPossibleMoves=0;
  for(int i=0;i<7;i++){
    if(b2->getBoard().at(0).at(i) == '-'){
      countPossibleMoves++;
    }
  }
  while(!b2->isGameOver()){
    randCol = rand() % countPossibleMoves;
    int row = b2->getRow(randCol);
    b2->playMCTS(randCol);
    int win = b2->checkWin(row,randCol);
    if(win == 1){
      return 1; //AI WON
    }else if(win == 0){
      return -1; //PLAYER WON
    }
  }
  return 0; //draw
}

void MCTS::backpropagate(node *n, int win){
  node *cur = n;
  while(cur != NULL){
    cur->games++;
    cur->wins+=win;
    cur = cur->parent;
  }
}
