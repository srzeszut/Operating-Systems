CC=gcc
CFLAGS=-Wall
SA=sigaction_test

all: sigaction

sigaction: $(SA).c
	$(CC) $(CFLAGS) -c $(SA).c
	$(CC) $(CFLAGS) $(SA).o -o $(SA)

clean:
	rm -f *.o $(SA)