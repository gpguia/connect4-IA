#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>

using namespace std;

class Board{
    private:
        vector < vector <int> > board;
    public:
        Board();
        void printBoard();
        int play(int column);
};

#endif