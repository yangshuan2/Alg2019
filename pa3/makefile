# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
OPTFLAGS = -O3

all	: cb
	@echo -n ""

# optimized version
cb				: graph_opt.o main_opt.o
			$(CC) $(OPTFLAGS) graph_opt.o main_opt.o -o cb
main_opt.o 	   	: src/main.cpp src/graph.h src/maxHeap.h
			$(CC) $(CFLAGS) $< -o $@
graph_opt.o		: src/graph.cpp src/graph.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o cb
