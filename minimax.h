#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include <queue>
#include <ctime>
#include <cstdlib>

class Minimax{
    private:
        Board *b;
    public:
        void printt(int num);
        Minimax(Board *b); 
        virtual ~Minimax();
        queue <MATRIX> children(Board *pb, char turn);
        int max_value(int depth, int limit);
        int min_value(int depth, int limit);
        int minimax();
};

#endif