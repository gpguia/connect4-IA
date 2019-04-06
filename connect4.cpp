#include "connect4.h"

using namespace std;

double vm=0, rss=0; //to get maximum mem usage

enum{
  minimax = 1,
  alfabeta = 2,
  mcts = 3
};


int main(void){
    int algorithm, depth, row, column, checkPlay, win, first2Play;
    Board *b = new Board();
    clock_t tStart,tEnd;

    readInput(&algorithm,&depth,&first2Play);
    if(first2Play == 1){
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

                  //start timer
                  tStart = clock();
                  Minimax *mm = new Minimax();
                  column = mm->minimax(b,depth);
                  /* MEMORY USAGE */
                	double nowRSS, nowVM;
                	process_mem_usage(nowVM,nowRSS);
                	if(nowVM > vm)
                		vm = nowVM;

                	if(nowRSS > rss)
                    rss = nowRSS;
                  tEnd = clock();
                  cout << "\nAI Selected column: " << column+1 << endl;
                  cout << "Runtime: " << (double)(tEnd - tStart)/CLOCKS_PER_SEC << " segs" << endl;
                  cout << "VM: " << vm << "; RSS: " << rss << endl;
                  checkPlay = b->play(column);
                  if(checkPlay != 2 && checkPlay != -1){
                      break;
                  }
                  delete(mm);
                  b->setTurn('X');
              }
          }
          //add the last pice
          b->printBoard();
        break;

        case alfabeta :

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

                Alphabeta *ab = new Alphabeta();
                //start timer
                tStart = clock();

                column = ab->alphabeta(b,-513,513,depth);
                /* MEMORY USAGE */
                double nowRSS, nowVM;
                process_mem_usage(nowVM,nowRSS);
                if(nowVM > vm)
                  vm = nowVM;

                if(nowRSS > rss)
                  rss = nowRSS;
                tEnd = clock();
                cout << "\nAI Selected column: " << column+1 << endl;
                cout << "Runtime: " << (double)(tEnd - tStart)/CLOCKS_PER_SEC << " segs" << endl;
                cout << "VM: " << vm << "; RSS: " << rss << endl;
                checkPlay = b->play(column);
                if(checkPlay != 2 && checkPlay != -1){
                    break;
                }
                delete(ab);
                b->setTurn('X');
            }
        }
        b->printBoard();
        break;

        case mcts :
        MCTS *mc = new MCTS();
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

                //start timer
                tStart = clock();
                column = mc->mcts(b,1000000,false);
                /* MEMORY USAGE */
                double nowRSS, nowVM;
                process_mem_usage(nowVM,nowRSS);
                if(nowVM > vm)
                  vm = nowVM;

                if(nowRSS > rss)
                  rss = nowRSS;
                tEnd = clock();
                cout << "\nAI Selected column: " << column+1 << endl;
                cout << "Runtime: " << (double)(tEnd - tStart)/CLOCKS_PER_SEC << " segs" << endl;
                cout << "VM: " << vm << "; RSS: " << rss << endl;
                checkPlay = b->play(column);
                if(checkPlay != 2 && checkPlay != -1){
                    break;
                }
                b->setTurn('X');
            }
        }
        b->printBoard();
        break;
      }
    }else{
      switch(algorithm){

        case minimax :

          b->setTurn('O'); //AI STARTS
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

                  //start timer
                  tStart = clock();
                  Minimax *mm = new Minimax();
                  column = mm->minimax(b,depth);
                  /* MEMORY USAGE */
                	double nowRSS, nowVM;
                	process_mem_usage(nowVM,nowRSS);
                	if(nowVM > vm)
                		vm = nowVM;

                	if(nowRSS > rss)
                    rss = nowRSS;
                  tEnd = clock();
                  cout << "\nAI Selected column: " << column+1 << endl;
                  cout << "Runtime: " << (double)(tEnd - tStart)/CLOCKS_PER_SEC << " segs" << endl;
                  cout << "VM: " << vm << "; RSS: " << rss << endl;
                  checkPlay = b->play(column);
                  if(checkPlay != 2 && checkPlay != -1){
                      break;
                  }
                  delete(mm);
                  b->setTurn('X');
              }
          }
          //add the last pice
          b->printBoard();
        break;

        case alfabeta :

        b->setTurn('O'); //AI STARTS
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

                Alphabeta *ab = new Alphabeta();
                //start timer
                tStart = clock();

                column = ab->alphabeta(b,-513,513,depth);
                /* MEMORY USAGE */
                double nowRSS, nowVM;
                process_mem_usage(nowVM,nowRSS);
                if(nowVM > vm)
                  vm = nowVM;

                if(nowRSS > rss)
                  rss = nowRSS;
                tEnd = clock();
                cout << "\nAI Selected column: " << column+1 << endl;
                cout << "Runtime: " << (double)(tEnd - tStart)/CLOCKS_PER_SEC << " segs" << endl;
                cout << "VM: " << vm << "; RSS: " << rss << endl;
                checkPlay = b->play(column);
                if(checkPlay != 2 && checkPlay != -1){
                    break;
                }
                delete(ab);
                b->setTurn('X');
            }
        }
        b->printBoard();
        break;

        case mcts :
        MCTS *mc = new MCTS();
        b->setTurn('O'); //AI STARTS
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

                //start timer
                tStart = clock();
                column = mc->mcts(b,1000000,false);
                /* MEMORY USAGE */
                double nowRSS, nowVM;
                process_mem_usage(nowVM,nowRSS);
                if(nowVM > vm)
                  vm = nowVM;

                if(nowRSS > rss)
                  rss = nowRSS;
                tEnd = clock();
                cout << "\nAI Selected column: " << column+1 << endl;
                cout << "Runtime: " << (double)(tEnd - tStart)/CLOCKS_PER_SEC << " segs" << endl;
                cout << "VM: " << vm << "; RSS: " << rss << endl;
                checkPlay = b->play(column);
                if(checkPlay != 2 && checkPlay != -1){
                    break;
                }
                b->setTurn('X');
            }
        }
        b->printBoard();
        break;
      }
    }
    return 0;
}

void readInput(int *algorithm, int *depth, int *first2Play){
    printf("Please select an algorithm: \n\n");
    printf("1 - Minimax\n");
    printf("2 - Alpha-Beta\n");
    printf("3 - Monte Carlo tree search (MCTS)\n");
    scanf("%d",algorithm);
    while(*algorithm != 1 && *algorithm != 2 && *algorithm != 3){
        printf("\nPlease you must select a number from 1 to 3: \n");
        printf("Please select an algorithm: \n\n");
        printf("1 - Minimax\n");
        printf("2 - Alpha-Beta\n");
        printf("3 - Monte Carlo tree search (MCTS)\n");
        scanf("%d",algorithm);
    }
    if(*algorithm == 3){
      printf("Select frist to play: \n1 - Player Starts\n2 - AI - Starts\n");
      scanf("%d",first2Play);
      while(*first2Play != 1 && *first2Play != 2){
        printf("Select frist to play: \n1 - Player Starts\n2 - AI - Starts\n");
        scanf("%d",first2Play);
      }
      return;
    }
    printf("\nPlease select the difficulty: \n");
    printf("1 - Very Easy\n2 - Easy\n3 - Medium\n4 - Hard\n5 - Harder\n6 - Boss (It will take a while)\n");
    scanf("%d",depth);
    while(*depth != 1 && *depth != 2 && *depth != 3 && *depth != 4 && *depth != 5 && *depth != 6){
        printf("Please select a number from 1 to 6\n");
        scanf("%d",depth);
    }
    printf("Select frist to play: \n1 - Player Starts\n2 - AI - Starts\n");
    scanf("%d",first2Play);
    while(*first2Play != 1 && *first2Play != 2){
      printf("Select frist to play: \n1 - Player Starts\n2 - AI - Starts\n");
      scanf("%d",first2Play);
    }
}

void getPlayerCol(Board *b, int *col){
    b->printBoard();
    printf("\t\t1 2 3 4 5 6 7 \n");
    printf("Type column number: ");
    scanf("%d",col);
    *col = *col - 1;
}

//this funtion was taken from: https://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-runtime-using-c
//just to check memory usage, LINUX based, not sure if its working in MAC
void process_mem_usage(double& vm_usage, double& resident_set)
{
   //using std::ios_base;
   //using std::ifstream;
   //using std::string;

   vm_usage     = 0.0;
   resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}
