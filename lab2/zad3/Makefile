CC=gcc
CFLAGS=-Wall
DB=dirbytes
OPT_FLAG=-Os

all: bytes

bytes: $(DB).c
		$(CC) $(CFLAGS) $(OPT_FLAG) -c $(DB).c
		$(CC) $(CFLAGS) $(OPT_FLAG) $(DB).o -o $(DB)
clean:
		rm -f *.o $(DB) ?.txt ? valgrind-out.txt
