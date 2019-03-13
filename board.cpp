#include "connect4.h"

Board::Board(){
    for(int i=0;i<6;i++){
        vector<char> tmp;
        for(int j=0;j<7;j++){
            tmp.push_back('-');
        }
        board.push_back(tmp);
    }
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
    printf("\n\n\n\n");
}

MATRIX Board::getBoard(){
    return this->board;
}