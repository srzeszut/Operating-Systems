CC=gcc
CFLAGS=-Wall -Wpedantic -Werror
LIB=lib_wc
SOURCES= $(wildcard *.c)


all: static shared

static: $(SOURCES)
		$(CC) $(CFLAGS) -c $(SOURCES)
		ar rcs $(LIB).a $(SOURCES:.c=.o)

shared: $(SOURCES)
		$(CC) -fPIC -c $(CFLAGS) $(SOURCES)
		$(CC) -shared $(CFLAGS) -o $(LIB).so $(SOURCES:.c=.o)
clean:
		rm -f *.o *.a *.so
