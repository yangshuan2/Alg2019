# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
# DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: mps
	@echo -n ""

# optimized version
mps	: src/main.cpp src/mps.cpp src/mps.h
			$(CC) $(OPTFLAGS) src/main.cpp src/mps.cpp -o $@ -g

# clean all the .o and executable files
clean:
		rm -rf *.o mps
