#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>

using namespace std;

#define MATRIX vector < vector <char> >

class Board{
    private:
         MATRIX board;
    public:
        Board();
        MATRIX getBoard();
        void printBoard();
};

#endif