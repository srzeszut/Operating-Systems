CC=gcc
CFLAGS=-Wall
LIB=change_lib
SYS=change_sys


all: lib sys

lib: $(LIB).c
		$(CC) $(CFLAGS) -c $(LIB).c
		$(CC) $(CFLAGS) $(LIB).o -o $(LIB)

sys: $(SYS).c
		$(CC) $(CFLAGS) -c $(SYS).c
		$(CC) $(CFLAGS) $(SYS).o -o $(SYS)

clean:
		rm -f *.o $(LIB) $(SYS) *.txt