CC=gcc
CFLAGS=-Wall
CP=childProcess


all: proc

proc: $(CP).c
		$(CC) $(CFLAGS) -c $(CP).c
		$(CC) $(CFLAGS) $(CP).o -o $(CP)

clean:
		rm -f *.o $(CP)