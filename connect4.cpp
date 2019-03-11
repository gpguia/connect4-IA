#include "connect4.h"

using namespace std;

int main(void){
    Board* b = new Board();
    //b->printBoard();
    MATRIX bo = b->getBoard();
    b->printVec(bo[0]);
    return 0;
}