CC=gcc
CFLAGS=-Wall
SE=search


all: search test

search: $(SE).c
	$(CC) $(CFLAGS) -c $(SE).c
	$(CC) $(CFLAGS) $(SE).o -o $(SE)

test: search
	touch test1.txt && echo  "###" > test1.txt
	touch test2.txt && echo  "###" > test2.txt
	./$(SE) .. \# > wynik.txt

clean:
	rm -f *.o $(SE) *.txt