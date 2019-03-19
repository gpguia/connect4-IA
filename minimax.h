#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include "connect4.h"
#include <queue>

class Minimax{
    
    private:

    public:
        Minimax(); 
        virtual ~Minimax();
        int getNumRow(int col, MATRIX b);
        queue <MATRIX> children(MATRIX pBoard, char turn);
        int max_value(Board *b, int depth, int limit);
        int min_value(Board *b, int depth, int limit);
        
};

#endif