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

int Minimax::minimax(Board *b, int depth){
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

    if(child.checkPoints(row,column,'O') >= 4){
      result = 512;
    }else{
      result = min_value(child,1,depth);
    }

    if(result > maxValue){
      maxValue = result;
      retValue = column;
    }
    if(column < 6){
      column++;
    }
  }
  return retValue;
}


int Minimax::max_value(Board b, int depth, int limit){
  queue <Board> qChild = children(&b,'O');
  Board child;
  int col=0,row,result,maxValue=-513;

  if(depth == limit){
    return b.utility();
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

    if(child.checkPoints(row,col,'O') >= 4){
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

  if(depth == limit){
    return b.utility();
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

    /*if(checkPoints(child,row,col,'X') >= 4){
      result = -512;
    }else{
      result = max_value(child,depth+1,limit);
    }*/
    if(child.checkPoints(row,col,'X') >= 4){
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

/*
int Minimax::calcHor(Board b, int row, int col, char turn){
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

int Minimax::calcVert(Board b, int row, int col, char turn){
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

int Minimax::calcDig(Board b, int row, int col, char turn){
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

int Minimax::calcRDig(Board b, int row, int col, char turn){
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

int Minimax::utility(Board b){
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
*/
