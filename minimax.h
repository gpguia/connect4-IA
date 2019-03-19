#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include <queue>

class Minimax{
    
    private:
    int max(Board *b, int depth, int limit);
    int min(Board *b, int depth, int limit);
    queue <MATRIX> children(MATRIX pBoard, char turn);
    public:
    Minimax(); 
    virtual ~Minimax();

};

#endif