CC=gcc
CFLAGS=-Wall
INT=integral


all: integral test

integral: $(INT).c
	$(CC) $(CFLAGS) -c $(INT).c
	$(CC) $(CFLAGS) $(INT).o -o $(INT)

test: integral
	./$(INT) 0.00000001 1 > out.txt
	./$(INT) 0.00000001 5 >> out.txt
	./$(INT) 0.00000001 15 >> out.txt
	./$(INT) 0.00000001 50 >> out.txt
	./$(INT) 0.0001 1 >> out.txt
	./$(INT) 0.0001 5 >> out.txt
	./$(INT) 0.0001 15 >> out.txt
	./$(INT) 0.0001 50 >> out.txt




clean:
	rm -f *.o $(INT) out.txt