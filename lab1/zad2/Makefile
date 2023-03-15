CC=gcc
CFLAGS=-Wall
LIB=lib_wc
REPL=repl
DLL=dlopen.h



all: exe_static exe_shared exe_dll

static: $(LIB).c
		$(CC) $(CFLAGS) -c $(LIB).c
		ar rcs $(LIB).a $(LIB).o


shared: $(LIB).c
		$(CC) $(CFLAGS)  -fPIC -c $(LIB).c
		$(CC) $(CFLAGS) -shared  -o $(LIB).so $(LIB).o

exe_dll: shared $(LIB).h $(DLL)
		$(CC) $(CFLAGS) $(REPL).c $(DLL) -L . -Wl,-rpath,. -o $(REPL)_dll -ldl -D USE_DLL

exe_static: static $(LIB).h $(DLL)
		$(CC) $(CFLAGS) $(REPL).c   -o $(REPL)_static $(LIB).a

exe_shared: shared $(LIB).h $(DLL)
		$(CC) $(CFLAGS) $(REPL).c  -L . -Wl,-rpath,. -l:$(LIB).so  -o $(REPL)_shared

clean:
		rm -f *.o *.a *.so $(REPL)_static $(REPL)_shared $(REPL)_dll
