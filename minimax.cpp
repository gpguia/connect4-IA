#include "minimax.h"

Minimax::Minimax(){
}

Minimax::~Minimax(){
}


//pb = Parent Board
queue <Board> Minimax::children(Board *b, char turn){
    int row,column;
    queue <Board> q;
    Board child;
    for(column=0;column<7;column++){
        if(b->getBoard().at(0).at(column) == '-'){ //verify if the first line is playable
            child=*b;
            row = b->getRow(column);
            child.setPos(row,column,turn);
            q.push(child);
        }
    }
    return q;
}

int Minimax::checkPoints(Board b, int row, int col, char turn){
  return 0;
}

int Minimax::minimax(Board *b, int depth){
  queue <Board> qChild = children(b,'O');
  cout << "aqui" << endl;
  Board child;
  int column, result, maxValue = -513, row, retValue;

  while(!qChild.empty()){
    child = qChild.front();
    qChild.pop();

    for(int i=0;i<6;i++){
      if(b->getBoard().at(0).at(column) != '-'){
        column++;
      }
    }

    if(child.getBoard().at(0).at(column) == 'O'){
      row = 0;
    }else{
      row = child.getRow(column);
    }

    if(checkPoints(child,row,column,'O') >= 4){
      result = 512;
    }else{
      result = min_value(child,1,depth);
    }
    //REIRAR ISSO
    cout << "Result: " << result << ", Column = " << column+1 << endl;
  }

  if(result > maxValue){
    maxValue = result;
    retValue=column;
  }
  if(column < 6){
    column++;
  }
  cout << "retValue: " << retValue << endl;
  return retValue;
}


int Minimax::max_value(Board b, int depth, int limit){
  queue <Board> qChild = children(&b,'O');
  Board child;

  int col=0,row,result,maxValue=-513;

  while(!qChild.empty()){
    child = qChild.front();
    qChild.pop();

    while(b.getBoard().at(0).at(col) != '-' && col < 6){
      col++;
    }

    if(child.getBoard().at(0).at(col) == 'O'){
      row = 0;
    }else{
      row = child.getRow(col);
    }

    if(checkPoints(child,row,col,'O') >= 4){
      result = 512;
    }else{
      result = min_value(child,depth+1,limit);
    }

    if(result > maxValue){
      maxValue = result;
    }

    if(col < 6)
    col++;
  }
  return maxValue;
}

int Minimax::min_value(Board b, int depth, int limit){
    queue <Board> qChild = children(&b,'X');
    Board child;

    int col=0, row, result, minValue = 513;

    while(!qChild.empty()){
      child = qChild.front();
      qChild.pop();

      for(int i=0;i<6;i++){
        if(b.getBoard().at(0).at(col) != '-'){
          col++;
        }
      }

      if(child.getBoard().at(0).at(col) == 'X'){
        row = 0;
      }else{
        row = child.getRow(col);
      }

      if(checkPoints(child,row,col,'X') >= 4){
        result = -512;
      }else{
        result = max_value(child,depth+1,limit);
      }

      if(minValue > result){
        minValue = result;
      }

      if(col < 6){
        col++;
      }
      return minValue;
    }

    return minValue;
}
