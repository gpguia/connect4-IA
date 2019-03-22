#include "minimax.h"

Minimax::Minimax(Board *b){
    this->b = new Board();
    this->b = b;
}

Minimax::~Minimax(){
    free(this->b);
}


//pb = Parent Board
queue <Board> Minimax::children(char turn){
    int row,column;
    queue <Board> q;
    Board child;
    for(column=0;column<7;column++){
        if(this->b->getBoard().at(0).at(column) == '-'){ //verify if the first line is playable
            child=*b;
            row = this->b->getRow(column);
            child.setPos(row,column,turn);
            q.push(child);
        }
    }
    return q;
}


int Minimax::minimax(int depth){
    
    return 0;
}


int Minimax::max_value(int depth, int limit){
    return 0;
}

int Minimax::min_value(int depth, int limit){
    queue <Board> qChild = children(b->getTurn());
    Board node;

    int i=0, posi, result, minValue = 512;

    while(!qChild.empty()){
        node = qChild.front();
        qChild.pop();

        while(b->getBoard().at(0).at(i)=='-' && i < 6){
            i++;
        }
        if(node.getBoard().at(0).at(i)=='X'){
            posi = 0;
        }else{
            posi=node.getRow(i);
        }
        if(node.checkWin(posi,i) >= 4){
            result = -512;
        }else{
            result = max_value(depth+1,limit);
        }
        if(result < minValue){
            minValue = result;
        }
        if(i<6)
            i++;
    }
    return minValue;
}