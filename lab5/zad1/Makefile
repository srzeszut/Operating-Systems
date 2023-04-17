CC=gcc
CFLAGS=-Wall
MA=mail

all: mail

mail: $(MA).c
	$(CC) $(CFLAGS) -c $(MA).c
	$(CC) $(CFLAGS) $(MA).o -o $(MA)

clean:
	rm -f *.o $(MA)