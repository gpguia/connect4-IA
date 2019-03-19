#include "minimax.h"

Minimax::Minimax(){

}

Minimax::~Minimax(){
    //should free all memory used here
}


queue <MATRIX> children(MATRIX pBoard, char turn){
    int row,column;
    queue <MATRIX> q;
    MATRIX child;
    for(column=0;column<7;column++){
        if(pBoard[0][column] == '-'){ //verify if the first line is playable
            child=pBoard;
            child[row][column]=turn;
            row=getNumRow(column,pBoard);
            q.push(child);
        }
    }
    return q;
}

int Minimax::getNumRow(int col, MATRIX b){
    int r=0;
    for(int i=0;i<6;i++){
        if(b[i][col] == '-'){
            r++;
        }
    }
    r--;
    return r;
}

int Minimax::max_value(Board *b, int depth, int limit){
}

int Minimax::min_value(Board *b, int depth, int limit){

}