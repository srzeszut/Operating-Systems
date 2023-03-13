CC=gcc
CFLAGS=-Wall -c
LIB=lib_wc


all:
		make static
		make shared

static: $(LIB).c
		$(CC) $(CFLAGS) $(LIB).c
		ar rcs $(LIB).a $(LIB).o

shared:
		$(CC) -fPIC $(CFLAGS) $(LIB).c

clean:
		rm -f *.o *.a
