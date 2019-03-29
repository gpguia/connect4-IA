#include <iostream>
#include <stdlib.h>


#include "board.h"
#include "minimax.h"
#include "alphabeta.h"
#include "mcts.h"

#include <ctime>
#include <unistd.h>
#include <ios>
#include <fstream>

void readInput(int *algorithm, int *depth);
void getPlayerCol(Board *b,int *col);
void process_mem_usage(double& vm_usage, double& resident_set);
