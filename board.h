#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>

using namespace std;

#define MATRIX vector < vector <char> >


class Board{
    private:
         MATRIX board;
         char turn;
         
    public:
        Board();
        virtual ~Board();
        MATRIX getBoard();
        int getTurn();
        void printBoard();
        int checkWin(int x, int y);
        void setPos(int x, int y, int turn);
        void setTurn(char c);
        bool play(int col);
        int getRow(int col);
        void rmPos(int i, int j);
};

#endif