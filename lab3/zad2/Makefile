CC=gcc
CFLAGS=-Wall
BL=binls


all: ls

ls: $(BL).c
		$(CC) $(CFLAGS) -c $(BL).c
		$(CC) $(CFLAGS) $(BL).o -o $(BL)

clean:
		rm -f *.o $(BL)