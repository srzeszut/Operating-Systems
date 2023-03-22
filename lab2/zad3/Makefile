CC=gcc
CFLAGS=-Wall
DB=dirbytes
OPT_FLAG=-Os

all: bytes test

bytes: $(DB).c
		$(CC) $(CFLAGS) $(OPT_FLAG) -c $(DB).c
		$(CC) $(CFLAGS) $(OPT_FLAG) $(DB).o -o $(DB)
test: bytes
		./$(DB) . > porownanie.txt
		 wc dirbytes --bytes >>porownanie.txt
		 wc dirbytes.o --bytes >>porownanie.txt
		 wc dirbytes.c --bytes >>porownanie.txt
		 wc Makefile --bytes >>porownanie.txt
		 wc test.txt --bytes >>porownanie.txt
clean:
		rm -f *.o $(DB) ?.txt ? valgrind-out.txt porownanie.txt
