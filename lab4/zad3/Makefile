CC=gcc
CFLAGS=-Wall
CA=catcher
SE=sender

all: catcher sender

catcher: $(CA).c
	$(CC) $(CFLAGS) -c $(CA).c
	$(CC) $(CFLAGS) $(CA).o -o $(CA)

sender: $(SE).c
	$(CC) $(CFLAGS) -c $(SE).c
	$(CC) $(CFLAGS) $(SE).o -o $(SE)



clean:
	rm -f *.o $(CA) $(SE)