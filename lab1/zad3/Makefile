CC=gcc
CFLAGS=-Wall
LIB=lib_wc
REPL=repl
DLL=dlopen.h



all: exe_static exe_shared exe_dll tests_opt

tests_opt:
		make tests OPTI_FLAG="-O0"
		make tests OPTI_FLAG="-O1"
		make tests OPTI_FLAG="-O2"
		make tests OPTI_FLAG="-O3"
		make tests OPTI_FLAG="-Os"
		make tests OPTI_FLAG="-O"
o:
	make all OPTI_FLAG="-O"
o1:
	make all OPTI_FLAG="-O1"
o2:
	make all OPTI_FLAG"-O2"
o3:
	make all OPTI_FLAG="-O3"
os:
	make all OPTI_FLAG="-Os"
static: $(LIB).c
		$(CC) $(CFLAGS) $(OPTI_FLAG) -c $(LIB).c
		ar rcs $(LIB).a $(LIB).o


shared: $(LIB).c
		$(CC) $(CFLAGS) $(OPTI_FLAG) -fPIC -c $(LIB).c
		$(CC) $(CFLAGS) $(OPTI_FLAG) -shared  -o $(LIB).so $(LIB).o

exe_dll: shared $(LIB).h $(DLL)
		$(CC) $(CFLAGS) $(OPTI_FLAG) $(REPL).c $(DLL) -L . -Wl,-rpath,. -o $(REPL)_dll -ldl -D USE_DLL

exe_static: static $(LIB).h $(DLL)
		$(CC) $(CFLAGS) $(OPTI_FLAG) $(REPL).c   -o $(REPL)_static $(LIB).a

exe_shared: shared $(LIB).h $(DLL)
		$(CC) $(CFLAGS) $(OPTI_FLAG) $(REPL).c  -L . -Wl,-rpath,. -l:$(LIB).so  -o $(REPL)_shared

tests: exe_static exe_shared exe_dll
		./$(REPL)_static < tests.txt > test_static_$(OPTI_FLAG).txt
		./$(REPL)_shared < tests.txt > test_shared_$(OPTI_FLAG).txt
		./$(REPL)_dll < tests.txt > test_dll_$(OPTI_FLAG).txt

clean:
		rm -f *.o *.a *.so $(REPL)_static $(REPL)_shared $(REPL)_dll test_static*.txt test_shared*.txt test_dll*.txt
