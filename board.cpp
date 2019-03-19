#include "connect4.h"

Board::Board(){
    for(int i=0;i<6;i++){
        vector<char> tmp;
        for(int j=0;j<7;j++){
            tmp.push_back('-');
        }
        board.push_back(tmp);
    }
    this->turn = 'O';
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
		//if(posi-i>=0){
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
		//if(posi+i <= 5){
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

bool Board::play(int col){
    
    if(this->board[0][col] != '-' || col < 0 || col > 6){
        return false;
    }
    int row = this->getRow(col);
    this->setPos(row,col,this->turn);
    return true;
}

void Board::rmPos(int i, int j){
    this->setPos(i,j,'-');
}

