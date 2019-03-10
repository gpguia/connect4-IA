#include "board.h"

Board::Board(int x, int y){
    pr = x;
    pu = y;
}

int Board::getNumA(){
    return pu;
}