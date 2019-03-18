#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>

using namespace std;

#define MATRIX vector < vector <char> >

struct AiMove{
    AiMove() {};
    AiMove(int Score) : score(Score){}
    int x;
    int y;
    int score;
};

class Board{
    private:
         MATRIX board;
         char turn;
         int lastMove_x;
         int lastMove_y;
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
        void setLastMove(int x, int y);
        
        AiMove minimax(MATRIX board);
};

#endif