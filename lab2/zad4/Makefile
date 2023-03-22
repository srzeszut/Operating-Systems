CC=gcc
CFLAGS=-Wall
DF=dirftw
OPT_FLAG=-Os

all: search test

search: $(DF).c
		$(CC) $(CFLAGS) $(OPT_FLAG) -c $(DF).c
		$(CC) $(CFLAGS) $(OPT_FLAG) $(DF).o -o $(DF)

test: search
		mkdir -p tests/test1/test2
		touch tests/test1/test2/test1.txt tests/test1/test2.txt
		./$(DF) . > porownanie.txt
		find . |xargs wc --bytes >>porownanie.txt


clean:
		rm -f *.o $(DF) ?.txt ? valgrind-out.txt rm -r tests porownanie.txt
