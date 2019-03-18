#include "connect4.h"

using namespace std;


int main(void){
    int algorithm, depth, row, column;
    Board *b = new Board();

    //readInput(&algorithm,&depth);
    //printf("****** The Game has started ******\n");
    //getPlayerCol(b,&column);

    /*
    b->setPos(5,6,'O');
    b->setPos(4,5,'O');
    b->setPos(3,4,'O');
    b->setPos(2,3,'O');
    */
    b->setTurn('O'); //player 1 starts
    //b->printBoard();
    //cout << b->checkWin(0,0) << endl;

    getPlayerCol(b,&column);
    row = b->getRow(column);
    while(b->checkWin(row,column) == -1){
        b->setPos(row,column,b->getTurn());
        if(b->getTurn() == 'O'){
            b->setTurn('X');
            //IA PLAY
        }else{
            b->setTurn('O');
            //mudar funcoes de play para aqui. Quando ia ja jogar.
        }
        getPlayerCol(b,&column);
        row = b->getRow(column);
        cout << "row: " << row << endl;
        cout << "col: " << column << endl;
    }
    //add the last pice
    b->setPos(row,column,b->getTurn());
    b->printBoard();
    return 0;
}

void readInput(int *algorithm, int *depth){
    printf("Please select an algorithm: \n\n");
    printf("1 - Minimax\n");
    printf("2 - Alfa-Beta\n");
    printf("3 - Monte Carlo tree search (MCTS)\n");
    scanf("%d",algorithm);
    while(*algorithm != 1 && *algorithm != 2 && *algorithm != 3){
        printf("\nPlease you must select a number from 1 to 3: \n");
        printf("Please select an algorithm: \n\n");
        printf("1 - Minimax\n");
        printf("2 - Alfa-Beta\n");
        printf("3 - Monte Carlo tree search (MCTS)\n");
        scanf("%d",algorithm);
    }
    printf("\nPlease select the difficulty: \n");
    printf("1 - Very Easy\n2 - Easy\n3 - Medium\n4 - Hard\n5 - A Little harder\n6 - Boss\n");
    scanf("%d",depth);
    while(*depth != 1 && *depth != 2 && *depth != 3 && *depth != 4 && *depth != 5 && *depth != 6){
        printf("Please select a number from 1 to 6\n");
        scanf("%d",depth);
    }
}

void getPlayerCol(Board *b, int *col){
    b->printBoard();
    printf("\t\t1 2 3 4 5 6 7 \n");
    printf("Type column number: ");
    scanf("%d",col);
    *col = *col - 1;
}