#include "board.h"

Board::Board(){
    for(int i=0;i<6;i++){
        vector<int> tmp;
        for(int j=0;j<7;j++){
            tmp.push_back(-1);
        }
        board.push_back(tmp);
    }
}

void Board::printBoard(){
    for(int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int Board::play(int column){
    if(board[0][column] != -1 || column < 0 || column > 6){
        return -1;
    }
}
