CC=gcc
CFLAGS=-Wall
LIB=change_lib
SYS=change_sys
TEST1:= c U Makefile badmakefiletmp.txt
TEST2:= } B change_lib.c badchangeBtmp.txt
TEST3:= = 9 change_sys.c badchange9tmp.txt
TEST4:= a b Makefile badmakefiletmp.txt ; tr a b < Makefile > tmp ; diff -s tmp badmakefiletmp.txt >dif.txt


all: lib sys time

lib: $(LIB).c
		$(CC) $(CFLAGS) -c $(LIB).c
		$(CC) $(CFLAGS) $(LIB).o -o $(LIB)

sys: $(SYS).c
		$(CC) $(CFLAGS) -c $(SYS).c
		$(CC) $(CFLAGS) $(SYS).o -o $(SYS)

time: sys lib
		./$(LIB) $(TEST1) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST1) >>  pomiar_zad_1.txt
		./$(LIB) $(TEST2) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST2) >>  pomiar_zad_1.txt
		./$(LIB) $(TEST3) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST3) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST4) >>  pomiar_zad_1.txt
		./$(SYS) $(TEST4) >>  pomiar_zad_1.txt

clean:
		rm -f *.o $(LIB) $(SYS) *.txt tmp