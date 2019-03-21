#include "minimax.h"

Minimax::Minimax(Board *b){
    this->b = new Board();
    this->b = b;
}

Minimax::~Minimax(){
    free(this->b);
}


//pb = Parent Board
queue <MATRIX> Minimax::children(Board *pb, char turn){
    int row,column;
    queue <MATRIX> q;
    MATRIX child;
    for(column=0;column<7;column++){
        if(pb->getBoard()[0][column] == '-'){ //verify if the first line is playable
            child=pb->getBoard();
            row = pb->getRow(column);
            child[row][column]=turn;
            q.push(child);
        }
    }
    return q;
}

int Minimax::minimax(){
    return rand() % 7;
}


int Minimax::max_value(int depth, int limit){
    return 0;
}

int Minimax::min_value(int depth, int limit){
    return 0;
}