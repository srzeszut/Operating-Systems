CC=gcc
CFLAGS=-Wall
LIB=change_lib
SYS=change_sys
TEST1:= c U Makefile tmp1.txt
TEST2:= } B change_lib.c tmp2.txt
TEST3:= = 9 change_sys.c tmp3.txt
TEST4:= a b Makefile tmp1.txt >/dev/null; tr a b < Makefile > tmp ; diff -s tmp tmp1.txt >dif.txt
OPT_FLAG=-Os

all: lib sys time

lib: $(LIB).c
		$(CC) $(CFLAGS) $(OPT_FLAG) -c $(LIB).c
		$(CC) $(CFLAGS) $(OPT_FLAG) $(LIB).o -o $(LIB)

sys: $(SYS).c
		$(CC) $(CFLAGS) $(OPT_FLAG) -c $(SYS).c
		$(CC) $(CFLAGS) $(OPT_FLAG) $(SYS).o -o $(SYS)

time: sys lib
		./$(LIB) $(TEST1) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST1) >>  pomiar_zad_1.txt
		./$(LIB) $(TEST2) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST2) >>  pomiar_zad_1.txt
		./$(LIB) $(TEST3) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST3) >>  pomiar_zad_1.txt
		./$(LIB) $(TEST4) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST4) >>  pomiar_zad_1.txt

clean:
		rm -f *.o $(LIB) $(SYS) tmp?.txt tmp dif.txt