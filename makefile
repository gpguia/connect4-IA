OBJS=connect4.o board.o minimax.o alphabeta.o mcts.o
CC=g++
PROGRAM=./connect4
CFLAGS=-std=c++11
INDIR=./inputs/


all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS)

test: $(PROGRAM)
	$(PROGRAM) < $(INDIR)example1.txt
