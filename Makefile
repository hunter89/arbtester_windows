CC=clang++

CFLAGS=-c -g
CLIB=-LC:/gurobi751/win64/lib/ -lgurobi75 -lgurobi_c++md2015 -lgurobi_c++md2017 -lgurobi_c++mdd2015 -lgurobi_c++mdd2017
INC=C:/gurobi751/win64/include/ 

#to make all of the files
all: hello

hello: arbplus.o parser.o output.o sensitivity.o CreateHistCsv.o
		$(CC) arbplus.o parser.o output.o sensitivity.o CreateHistCsv.o -o hello

arbplus.o: arbplus.cpp
		$(CC) $(CFLAGS) arbplus.cpp

parser.o: parser.cpp
		$(CC) $(CFLAGS) parser.cpp

output.o: output.cpp
		$(CC) $(CFLAGS) output.cpp

#solver.o: solver.cpp
#		$(CC) $(CFLAGS) -I $(INC) solver.cpp

sensitivity.o: sensitivity.cpp
		$(CC) $(CFLAGS) sensitivity.cpp

CreateHistCsv.o: CreateHistCsv.cpp
		$(CC) $(CFLAGS) CreateHistCsv.cpp

clean:
		rm -rf *o hello
