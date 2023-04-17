CC=gcc
CFLAGS=-Wall
INT=integral
CO=count


all: integral test

integral: $(INT).c $(CO).c
	$(CC) $(CFLAGS) -c $(CO).c
	$(CC) $(CFLAGS) $(CO).o -o $(CO)
	$(CC) $(CFLAGS) -c $(INT).c
	$(CC) $(CFLAGS) $(INT).o -o $(INT)

test: integral
	./$(INT) 0.000000001 10 > out.txt
	./$(INT) 0.000000001 50 >> out.txt
	./$(INT) 0.000000001 150 >> out.txt
	./$(INT) 0.000000001 1500 >> out.txt
	./$(INT) 0.000000001 2000 >> out.txt
	./$(INT) 0.0001 1 >> out.txt
	./$(INT) 0.0001 5 >> out.txt
	./$(INT) 0.0001 15 >> out.txt
	./$(INT) 0.0001 50 >> out.txt




clean:
	rm -f *.o $(INT) $(CO) out.txt