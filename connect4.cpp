#include "connect4.h"

using namespace std;

enum{
  minimax = 1,
  alfabeta = 2,
  mcts = 3
};

int main(void){
    int algorithm, depth, row, column, checkPlay, win;
    Board *b = new Board();

    readInput(&algorithm,&depth);
    switch(algorithm){
      case minimax :
        b->setTurn('X'); //player 1 starts
        while(true){
            if(b->getTurn() == 'X'){
                getPlayerCol(b,&column);
                checkPlay = b->play(column);
                while(checkPlay == -1){
                    cout << "ERROR: invalid column." << endl;
                    getPlayerCol(b,&column);
                    checkPlay = b->play(column);
                }
                if(checkPlay != 2 && checkPlay != -1){
                    break;
                }
                b->setTurn('O');
            }else{
                //AI
                Board *aux = new Board();
                aux = b;
                Minimax *mm = new Minimax();
                column = mm->minimax(b,depth);
                cout << "column: " << column << endl;
                checkPlay = b->play(column);
                if(checkPlay != 2 && checkPlay != -1){
                    break;
                }
                free(mm);
                b->setTurn('X');
            }
        }
        //add the last pice
        b->printBoard();
      break;
      case alfabeta :

      break;

      case mcts :

      break;
    }
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
