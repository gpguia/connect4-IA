#include "minimax.h"

Minimax::Minimax(){

}

Minimax::~Minimax(){
    //should free all memory used here
}

queue <MATRIX> children(MATRIX pBoard, char turn){
    int row,column;
    queue <MATRIX>
}

int Minimax::min(Board *b, int depth, int limit){
    if(depth == limit){
        //calcular tudo
    }
    queue <MATRIX> qChildren = children(b->getBoard(), 'X');
}

int Minimax::max(Board *b, int depth, int limit){

}


