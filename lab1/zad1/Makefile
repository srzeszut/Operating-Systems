CC=gcc
CFLAGS=-Wall -c
LIB=lib_wc


all:
		make libstatic
		make libshared

libstatic: $(LIB).c
		$(CC) $(CFLAGS) $(LIB).c
		ar rcs $(LIB).a $(LIB).o

libshared:
		$(CC) -fPIC $(CFLAGS) $(LIB).c

clean:
		rm -f *.o *.a
