#include "connect4.h"

Board::Board(){
    for(int i=0;i<6;i++){
        vector<char> tmp;
        for(int j=0;j<7;j++){
            tmp.push_back('-');
        }
        board.push_back(tmp);
    }
    pts[0] = 0;
    pts[1] = 1;
    pts[2] = 10;
    pts[3] = 50;
    this->last_col=-1;
    this->last_row=-1;
}

Board::~Board() {
    this->board.clear();
}

void Board::printBoard(){
    printf("\n\n\n\n");
    for(int i=0;i<6;i++){
        printf("\t\t");
        for(int j=0;j<7;j++){
            printf("%c ",this->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

MATRIX Board::getBoard(){
    return this->board;
}

int Board::getTurn(){
    return this->turn;
}

void Board::setPos(int x, int y, int turn){
    if(turn == 'O')
        this->board[x][y] = 'O';
    else
        this->board[x][y] = 'X';
}

void Board::setTurn(char c){
    this->turn = c;
}

//return 1 if player win, return 2 if IA win
//x and y are the positions where the last pice was played
int Board::checkWin(int x, int y){
    int count=0;

    //check horizontal left
   for(int j=1;j<4;j++){
		if(x >= 0 && x <= 5 && y-j >= 0 && y-j <=6){
		//if(posj-j>=0){
			if(this->board[x][y - j] == this->turn){
				count++;
			}
        }
	}
    if(count == 3){//since board[x][y] is the same that was played we dont have to check it.
        if(this->turn == 'O')
            return 1; //player won
        else
            return 0; //IA WON
    }

    count=0;
    //check horizontal right
    for(int j=1;j<4;j++){
		//if(posj+j<=6){
		if(x >= 0 && x <= 5 && y+j >= 0 && y+j <=6){
			if(this->board[x][y + j] == this->turn){
				count++;
			}
        }
    }
    if(count == 3){//since board[x][y] is the same that was played we dont have to check it.
        if(this->turn == 'O')
            return 1; //player won
        else
            return 0; //IA WON
    }

    //checkVertUp
    count=0;
    for(int i=1;i<4;i++){
		if(x-i >= 0 && x-i <= 5 && y >= 0 && y <=6){
			if(this->board[x-i][y] == this->turn){
				count++;
			}
        }
    }

    if(count == 3){//since board[x][y] is the same that was played we dont have to check it.
        if(this->turn == 'O')
            return 1; //player won
        else
            return 0; //IA WON
    }

    //checkVertDown
    count=0;
    for(int i=1;i<4;i++){
		if(x+i >= 0 && x+i <= 5 && y >= 0 && y <=6){
			if(this->board[x+i][y] == this->turn){
				count++;
			}
        }
    }
    if(count == 3){//since board[x][y] is the same that was played we dont have to check it.
        if(this->turn == 'O')
            return 1; //player won
        else
            return 0; //IA WON
    }

    //diagLeft
    count=0;
    for(int i=1;i<4;i++){
        if(x+i < 6 && y-i >= 0){
            if(this->board[x+i][y-i]==this->turn)
                count++;
        }
    }
    if(count == 3){//since board[x][y] is the same that was played we dont have to check it.
        if(this->turn == 'O')
            return 1; //player won
        else
            return 0; //IA WON
    }
    //DiagRight
    count=0;
    for(int i=1;i<4;i++){
        if(x-i >= 0 && y+i < 7){
            if(this->board[x-i][y+i]==this->turn)
                count++;
        }
    }
    if(count == 3){//since board[x][y] is the same that was played we dont have to check it.
        if(this->turn == 'O')
            return 1; //player won
        else
            return 0; //IA WON
    }

    //reverseDiagLeft
    count=0;
    for(int i=1;i<4;i++){
        if(x+i < 6 && y+i < 7){
            if(this->board[x+i][y+i]==this->turn)
                count++;
        }
    }
    if(count == 3){//since board[x][y] is the same that was played we dont have to check it.
        if(this->turn == 'O')
            return 1; //player won
        else
            return 0; //IA WON
    }

    //reverseDiagRight
    count=0;
    for(int i=1;i<4;i++){
        if(x-i >= 0 && y-i >= 0){
            if(this->board[x-i][y-i] == this->turn)
                count++;
        }
    }
    if(count == 3){//since board[x][y] is the same that was played we dont have to check it.
        if(this->turn == 'O')
            return 1; //player won
        else
            return 0; //IA WON
    }

    return -1; //No one wins
}

int Board::getRow(int col){ //get a possible value of i to play
    int r=0;
    for(int i=0;i<6;i++){
        if(this->board[i][col] == '-'){
            r++;
        }
    }
    r--;
    return r;
}

int Board::play(int col){
    int win;
    if(this->board[0][col] != '-' || col < 0 || col > 6){
        return -1;
    }
    int row = this->getRow(col);
    this->setPos(row,col,this->turn);
    win = checkWin(row,col);
    if(win == 1){
        cout << "AI Won :D\n";
        return 1;
    }
    if(win == 0){
        cout << "Player 1 Won :D\n";
        return 0;
    }
    return 2;
}

void Board::rmPos(int col){
    int row = getRow(col);
    row++;
    this->setPos(row,col,'-');
}

int Board::calcHor(int row, int col, char turn){
  int total=0;
  char vsTurn;

	for(int j=col;j<col+4;j++){
		if(turn == '-')
				turn = this->board.at(row).at(j);
		if(turn != '-'){
			if(turn == 'X')
				vsTurn = 'O';
			else
				vsTurn = 'X';


			if(this->board.at(row).at(j) == vsTurn){
				return 0;
			}else if(this->board.at(row).at(j) == turn){
				total++;
			}
		}
	}

	if(turn == 'X'){
		return -pts[total];
	}
	return pts[total];
}

int Board::calcVert(int row, int col, char turn){
  int total=0,i,j;
	char vsTurn;

  if(turn == 'X')
      vsTurn = 'O';
  else
      vsTurn = 'X';

	for(i = row; i>row-4;i--){
		if(this->board.at(i).at(col) == vsTurn){
			return 0;
		}else if(this->board.at(i).at(col) == turn){
			total++;
		}
	}

	if(turn == 'X'){
		return -pts[total];
	}
	return pts[total];
}

int Board::calcDig(int row, int col, char turn){
  int total=0;
  char vsTurn;

  for(int k=0;k<4;k++){
  	if(turn == '-')
  		turn=this->board.at(row-k).at(col+k);

  	if(turn != '-'){

  		if(turn == 'X')
  			vsTurn = 'O';
  		else
  			vsTurn = 'X';

  		if(this->board.at(row-k).at(col+k) == vsTurn)
  			return 0;
  		else if(this->board.at(row-k).at(col+k) == turn)
  			total++;
  	}
  }

  if(turn == 'X'){
  	return -pts[total];
  }
  return pts[total];
}

int Board::calcRDig(int row, int col, char turn){
  int total=0;
  char vsTurn;


  for(int k=0;k<4;k++){
    if(turn == '-')
      turn=this->board.at(row+k).at(col+k);
    if(turn != '-'){
      if(turn == 'X')
        vsTurn = 'O';
      else
        vsTurn = 'X';

      if(this->board.at(row+k).at(col+k) == vsTurn)
        return 0;
      else if(this->board.at(row+k).at(col+k) == turn)
        total++;
    }
  }

  if(turn == 'X'){
    return -pts[total];
  }
  return pts[total];
}


int Board::utility(){
  int totalHor=0,totalVer=0,totalDig=0,totalRDig=0;
  //Horizontal
  for(int i=0;i<6;i++){
    for(int j=0;j<4;j++){
      char t = this->board.at(i).at(j);
      totalHor += calcHor(i, j, t);
    }
  }
  //Vertical
  for(int j=0;j<7;j++){
    for(int i=5;i>2;i--){
      if(this->board.at(i).at(j) != '-'){
        char t = this->board.at(i).at(j);
        totalVer += calcVert(i, j, t);
      }
    }
  }
  //Diagonal
	for(int i=3;i<6;i++){
		for(int j=0;j<4;j++){
      char t = this->board.at(i).at(j);
			totalDig += calcDig(i, j, t);
		}
	}
  //Reverse Diagonal
	for(int i=0;i<3;i++){
		for(int j=0;j<4;j++){
      char t = this->board.at(i).at(j);
			totalRDig += calcRDig(i, j, t);
		}
	}
  return totalHor + totalVer + totalDig + totalRDig;
}

int Board::checkPoints(int row, int col, char turn){
  int horLeft=0,horRight=0,verUp=0,verDown=0,digLeft=0,digRight=0,rDiagLeft=0,rDiagRight=0;
  int totalHor, totalVer, totalDig, totalRDig;

//horizontalLeft
  for(int j=1;j<4;j++){
    if(row >= 0 && row <= 5 && col-j >= 0 && col-j <= 6){
      if(this->board.at(row).at(col-j) == turn)
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
      if(this->board.at(row).at(col+j) == turn)
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
      if(this->board.at(row-i).at(col) == turn)
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
      if(this->board.at(row+i).at(col) == turn)
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
      if(this->board.at(row+i).at(col-i) == turn)
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
      if(this->board.at(row-i).at(col+i) == turn)
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
      if(this->board.at(row+i).at(col+i) == turn)
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
        if(this->board.at(row-i).at(col-i) == turn)
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

int Board::checkWinMCTS(){
  int win = checkWin(this->last_row,this->last_col);
  if(win == 1){
    return 1;
  }else if(win == 0){
    return -1;
  }
  return 0;
}


//play function for MCTS, it will not display who own and change turns auto
void Board::playMCTS(int col){
  while(this->board.at(0).at(col) != '-' && col < 6){
      col++;
  }

  int row = getRow(col);
  this->last_row = row;
  this->last_col = col;
  if(this->turn == 'X'){
    this->setPos(row,col,'X');
    this->setTurn('O');
    return;
  }
  this->setPos(row,col,'O');
  this->setTurn('X');
  return;
}

Board *Board::dup(){
  Board *b2 = new Board();
  for(int i=0;i<6;i++){
    for(int j=0;j<7;j++){
      b2->board[i][j] = this->board[i][j];
      b2->last_row = this->last_row;
      b2->last_col = this->last_col;
    }
  }
  return b2;
}

bool Board::isColumnFree(int col){
  return !(this->board.at(0).at(col) == '-');
}

vector<int> Board::getPlays(){
  vector<int> plays;
  for(int i=0;i<7;i++){
    if(this->board[0][i] == '-'){
      plays.push_back(i);
    }
  }
  return plays;
}

bool Board::isBoardFull(){
  int count=0;
  for(int i=0;i<7;i++){
    if(this->board[0][i] != '-'){
      count++;
    }
  }
  if(count == 7)
    return true;
  return false;
}
