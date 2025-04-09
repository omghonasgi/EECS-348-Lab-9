CC = g++
CFLAGS = -c -Wall


all: prog

prog: matrix.o
	$(CC) $(CDFLAGS) matrix.o -o prog

matrix.o: matrix.cpp
	$(CC) $(CFLAGS) matrix.cpp

clean:
	rm -rf *.o prog
