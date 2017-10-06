CC=clang++

CFLAGS=-c -g
CLIB=-L/Library/gurobi751/mac64/lib/ -lgurobi75 -lgurobi_c++
INC=/Library/gurobi751/mac64/include/ 

#to make all of the files
all: hello

hello: arbplus.o output.o solver.o sensitivity.o CreateHistCsv.o
		$(CC) $(CLIB) arbplus.o output.o solver.o sensitivity.o CreateHistCsv.o -o hello

arbplus.o: arbplus.cpp
		$(CC) $(CFLAGS) arbplus.cpp

#parser.o: parser.cpp
#		$(CC) $(CFLAGS) parser.cpp

output.o: output.cpp
		$(CC) $(CFLAGS) output.cpp

solver.o: solver.cpp
		$(CC) $(CFLAGS) -I $(INC) solver.cpp

sensitivity.o: sensitivity.cpp
		$(CC) $(CFLAGS) sensitivity.cpp

CreateHistCsv.o: CreateHistCsv.cpp
		$(CC) $(CFLAGS) CreateHistCsv.cpp

clean:
		rm -rf *o hello