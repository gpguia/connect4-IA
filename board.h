#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>

using namespace std;

#define MATRIX vector < vector <int> >

class Board{
    private:
         MATRIX board;
    public:
        Board();
        void printBoard();
        int play(int column);
        void printVec(vector<int> v);
        MATRIX getBoard();
        
};

#endif