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
  int horLeft=0,horRight=0,verUp=0,verDown=0,digLeft=0,digRight=0,rDiagLeft=0,rDiagRight=0;
  int totalHor, totalVer, totalDig, totalRDig;

//horizontalLeft
  for(int j=1;j<4;j++){
    if(row >= 0 && row < 6 && col-j >= 0 && col-j < 7){
      if(b.getBoard().at(row).at(col-j) == turn)
        horLeft++;
      else
        break;
    }else{
      break;
    }

  }
//horizontalRight
  for(int j=1;j<4;j++){
    if(row >= 0 && row < 6 && col+j >= 0 && col+j < 7){
      if(b.getBoard().at(row).at(col+j) == turn)
        horRight++;
      else
        break;
    }else{
      break;
    }
  }
//verticalUp
  for(int i=1;i<4;i++){
    if(row-i >= 0 && row-i < 6 && col >= 0 && col < 7){
      if(b.getBoard().at(row-i).at(col) == turn)
        verUp++;
      else
        break;
      }else{
        break;
      }
    }
//verticalDown
  for(int i=1;i<4;i++){
    if(row+i >= 0 && row+i < 6 && col >= 0 && col < 7){
      if(b.getBoard().at(row+i).at(col) == turn)
        verDown++;
      else
        break;
    }else{
      break;
    }
  }
//diagLeft
  for(int i=1;i<4;i++){
    if(row+i < 6 && col-i >= 0){
      if(b.getBoard().at(row+i).at(col-i) == turn)
        digLeft++;
      else
        break;
    }else{
      break;
    }
  }

//diagRight
  for(int i=1;i<4;i++){
    if(row-i >= 0 && col+i < 7){
      if(b.getBoard().at(row-i).at(col+i) == turn)
        digRight++;
      else
        break;
    }else{
      break;
    }
  }
//reverseDiagLeft
  for(int i=1;i<4;i++){
    if(row+i < 6 && col+i < 7){
      if(b.getBoard().at(row+i).at(col+i) == turn)
        rDiagLeft++;
      else
        break;
    }else{
      break;
    }
  }

//reverseDiagRight
  for(int i=1;i<4;i++){
      if(row-i >= 0 && col-i >= 0){
        if(b.getBoard().at(row-i).at(col-i) == turn)
          rDiagRight++;
        else
          break;
      }else{
        break;
      }
  }

  totalHor = horLeft + horRight + 1;
  totalVer = verUp + verDown + 1;
  totalDig = digLeft + digRight + 1;
  totalRDig = rDiagLeft + rDiagRight + 1;
  return max(totalHor, max(totalVer, max(totalDig,totalRDig)));

}

int Minimax::minimax(Board *b, int depth){
  queue <Board> qChild = children(b,'O');
  Board child;
  int column=0, result, maxValue = -513, row, retValue;

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

int Minimax::utility(Board b){
  int totalHor=0,totalVer=0,totalDig=0,totalRDig=0;
  for(int i=0;i<6;i++){
    for(int j=0;j<4;j++){
      totalHor += calcHor();
    }
  }


}
