#include "alphabeta.h"

Alphabeta::Alphabeta(){
  pts[0] = 0;
  pts[1] = 1;
  pts[2] = 10;
  pts[3] = 50;
}

Alphabeta::~Alphabeta(){

}

int Alphabeta::alphabeta(Board *b, int alpha, int beta, int depth){
  queue <Board> qChild = children(b,'O');
  Board child;
  int column=0, result, maxValue = -513, row, retValue;


  for(int i=0;i<7;i++){//verify if there is an win play for AI
    int row, win;
    row = b->getRow(i);
    win = b->checkWin(row,i);
    if(win == 1){
      return i;
    }
  }

  while(!qChild.empty()){
    child = qChild.front();
    qChild.pop();

    //verify if first column is full
    while(b->getBoard().at(0).at(column) != '-' && column < 6){
        column++;
    }

    if(child.getBoard().at(0).at(column) == 'O'){
      row = 0;
    }else{
      row = child.getRow(column);
    }
    int c = checkPoints(child,row,column,'O');
    if(c >= 4){
      result = 512;
    }else{
      result = min_value(child,alpha,beta,1,depth); //depth is limit int that function
    }

    if(result > maxValue){
      maxValue = result;
      retValue = column;
    }

    if(result >= beta){
      return retValue;
    }
    alpha = max(alpha,result);
    if(column < 6){
      column++;
    }
  }
  return retValue;
}

int Alphabeta::max_value(Board b, int alpha, int beta, int depth, int limit){
  queue <Board> qChild = children(&b,'O');
  Board child;
  int col=0,row,result,maxValue=-513;

  if(depth == limit){
    return utility(b);
  }

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
      result = min_value(child,alpha,beta,depth+1,limit);
    }

    if(result > maxValue){
      maxValue = result;
    }
    if(result >= beta)
      return result;
      
    alpha = max(alpha,result);

    if(col < 6)
    col++;
  }
  return maxValue;
}

int Alphabeta::min_value(Board b, int alpha, int beta, int depth, int limit){
  queue <Board> qChild = children(&b,'X');
  Board child;
  int col=0, row, result, minValue = 513;

  if(depth == limit){
    int u = utility(b);
    return u;
  }

  while(!qChild.empty()){
    child = qChild.front();
    qChild.pop();

    while(b.getBoard().at(0).at(col) !='-' && col < 6)
			col++;

    if(child.getBoard().at(0).at(col) == 'X'){
      row = 0;
    }else{
      row = child.getRow(col);
    }

    if(checkPoints(child,row,col,'X') >= 4){
      result = -512;
    }else{
      result = max_value(child,alpha,beta,depth+1,limit);
    }

    if(minValue > result){
      minValue = result;
    }

    if(alpha >= result)
      return result;

    beta = min(beta,result);

    if(col < 6){
      col++;
    }
    return minValue;
  }
  return minValue;
}



queue <Board> Alphabeta::children(Board *b, char turn){
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

int Alphabeta::checkPoints(Board b, int row, int col, char turn){
  int horLeft=0,horRight=0,verUp=0,verDown=0,digLeft=0,digRight=0,rDiagLeft=0,rDiagRight=0;
  int totalHor, totalVer, totalDig, totalRDig;

//horizontalLeft
  for(int j=1;j<4;j++){
    if(row >= 0 && row <= 5 && col-j >= 0 && col-j <= 6){
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
    if(row-i >= 0 && row-i <= 5 && col >= 0 && col <= 6){
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
    if(row+i >= 0 && row+i <= 5 && col >= 0 && col <= 6){
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
  totalRDig = rDiagLeft + rDiagRight+ 1;
  return max(totalHor, max(totalVer, max(totalDig,totalRDig)));

}

int Alphabeta::calcHor(Board b, int row, int col, char turn){
  int total=0;
  char vsTurn;

	for(int j=col;j<col+4;j++){
		if(turn == '-')
				turn = b.getBoard().at(row).at(j);
		if(turn != '-'){
			if(turn == 'X')
				vsTurn = 'O';
			else
				vsTurn = 'X';


			if(b.getBoard().at(row).at(j) == vsTurn){
				return 0;
			}else if(b.getBoard().at(row).at(j) == turn){
				total++;
			}
		}
	}

	if(turn == 'X'){
		return -pts[total];
	}
	return pts[total];
}

int Alphabeta::calcVert(Board b, int row, int col, char turn){
  int total=0,i,j;
	char vsTurn;

  if(turn == 'X')
      vsTurn = 'O';
  else
      vsTurn = 'X';

	for(i = row; i>row-4;i--){
		if(b.getBoard().at(i).at(col) == vsTurn){
			return 0;
		}else if(b.getBoard().at(i).at(col) == turn){
			total++;
		}
	}

	if(turn == 'X'){
		return -pts[total];
	}
	return pts[total];
}

int Alphabeta::calcDig(Board b, int row, int col, char turn){
  int total=0;
  char vsTurn;

  for(int k=0;k<4;k++){
  	if(turn == '-')
  		turn=b.getBoard().at(row-k).at(col+k);

  	if(turn != '-'){

  		if(turn == 'X')
  			vsTurn = 'O';
  		else
  			vsTurn = 'X';

  		if(b.getBoard().at(row-k).at(col+k) == vsTurn)
  			return 0;
  		else if(b.getBoard().at(row-k).at(col+k) == turn)
  			total++;
  	}
  }

  if(turn == 'X'){
  	return -pts[total];
  }
  return pts[total];
}

int Alphabeta::calcRDig(Board b, int row, int col, char turn){
  int total=0;
  char vsTurn;


  for(int k=0;k<4;k++){
    if(turn == '-')
      turn=b.getBoard().at(row+k).at(col+k);
    if(turn != '-'){
      if(turn == 'X')
        vsTurn = 'O';
      else
        vsTurn = 'X';

      if(b.getBoard().at(row+k).at(col+k) == vsTurn)
        return 0;
      else if(b.getBoard().at(row+k).at(col+k) == turn)
        total++;
    }
  }

  if(turn == 'X'){
    return -pts[total];
  }
  return pts[total];
}

int Alphabeta::utility(Board b){
  int totalHor=0,totalVer=0,totalDig=0,totalRDig=0;
  //Horizontal
  for(int i=0;i<6;i++){
    for(int j=0;j<4;j++){
      char t = b.getBoard().at(i).at(j);
      totalHor += calcHor(b, i, j, t);
    }
  }
  //Vertical
  for(int j=0;j<7;j++){
    for(int i=5;i>2;i--){
      if(b.getBoard().at(i).at(j) != '-'){
        char t = b.getBoard().at(i).at(j);
        totalVer += calcVert(b, i, j, t);
      }
    }
  }
  //Diagonal
	for(int i=3;i<6;i++){
		for(int j=0;j<4;j++){
      char t = b.getBoard().at(i).at(j);
			totalDig += calcDig(b, i, j, t);
		}
	}
  //Reverse Diagonal
	for(int i=0;i<3;i++){
		for(int j=0;j<4;j++){
      char t = b.getBoard().at(i).at(j);
			totalRDig += calcRDig(b, i, j, t);
		}
	}
  return totalHor + totalVer + totalDig + totalRDig;
}
