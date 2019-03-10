#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>


class Board{
    private:
        int pr;
    public:
        Board(int x, int y);
        int pu;
        int getNumA();
};

#endif