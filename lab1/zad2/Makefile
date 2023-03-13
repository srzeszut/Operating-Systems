CC=gcc
CFLAGS=-Wall
LIB=lib_wc
REPL=repl


all:
		make run_static
		#make shared

static: $(LIB).c
		$(CC) $(CFLAGS) -c $(LIB).c
		ar rcs $(LIB).a $(LIB).o


shared:
		$(CC) -fPIC $(CFLAGS) -c $(LIB).c

run_static: static
		$(CC) $(CFLAGS) $(REPL).c $(LIB).a -o $(REPL)_static


clean:
		rm -f *.o *.a $(REPL)_static
