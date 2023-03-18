CC=gcc
CFLAGS=-Wall
CP=copy

all: cp

cp: $(CP).c
		$(CC) $(CFLAGS) -c $(CP).c
		$(CC) $(CFLAGS) $(CP).o -o $(CP)
clean:
		rm -f *.o $(CP)
