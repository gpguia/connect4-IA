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
        int play(int col);
        int getRow(int col);
        void rmPos(int col);
        int fullCheck();
};

#endif
