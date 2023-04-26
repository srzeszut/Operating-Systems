CC=gcc
CFLAGS=-Wall
SB=sleepingBarber_POSIX
OTHER:=semph.c queue.c

all: prog client barber test

prog: $(SB).c client barber
	$(CC) $(CFLAGS) $(SB).c $(OTHER) -o $(SB)

client: client.c
	$(CC) $(CFLAGS) client.c $(OTHER) -o client

barber: barber.c
	$(CC) $(CFLAGS)  barber.c $(OTHER) -o barber
test: prog
	./$(SB) 3 4 2 > out.txt


clean:
	rm -f *.o client barber  $(SB) out.txt