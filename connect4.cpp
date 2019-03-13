#include "connect4.h"

using namespace std;


int main(void){
    int algorithm, depth;
    Board *b = new Board();

    readInput(&algorithm,&depth);
    start(b);

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

void start(Board *b){
    printf("****** The Game has started ******\n");
    b->printBoard();
    
}