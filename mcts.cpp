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

  while(clock() - start_time < time_limit){
    n = root;
    if(n == NULL){
      continue;
    }

    child = expand(n);
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

node *MCTS::select(node *root){
  for(int i=0;i<7;i++){
    if(root->children[i] == NULL && !root->board->isColumnFree(i))
      return root;
  }
  double maxVal = -1;
  int maxIndex = -1;
  for(int i=0;i<7;i++){
    if(root->board->isColumnFree(i))
      continue;

    node *cur = root->children[i];
    double wins;
    if(root->board->getTurn() == 'X'){
      wins = (double)cur->wins;
    }else{
      wins = (double)(cur->games - cur->wins);
    }
    double val = (wins/cur->games) + sqrt(2)*sqrt(log(root->games)/cur->games);
    if(val > maxVal){
      maxVal = val;
      maxIndex = i;
    }
  }
  if(maxVal == -1)
    return NULL;
  return select(root->children[maxIndex]);
}

node *MCTS::expand(node *n){
  vector<int> arrToVisit;
  arrToVisit.resize(7);
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
  delete(b3);
  return n->children[k];
}

int MCTS::simulate(node *n){
  int randCol=0;
  Board *b2 = n->board->clone();
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
  delete(b2);
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
