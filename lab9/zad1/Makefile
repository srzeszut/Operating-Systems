CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: santa

santa: main.c
	$(CC) $(CFLAGS) main.c -o $@

clean:
	rm -f santa