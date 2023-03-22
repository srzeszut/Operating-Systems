CC=gcc
CFLAGS=-Wall
CP=copy
OPT_FLAG=-Os
TEST1:= test.txt rev1.txt
TEST2:= copy.c rev2
TEST3:= Makefile rev3.txt
TEST5:= tmp1 tmp2




all:
	make time BLOCK=1
	make time BLOCK=1024



cp: $(CP).c
		$(CC) $(CFLAGS) $(OPT_FLAG) -c $(CP).c -D BLOCK_SIZE=$(BLOCK)
		$(CC) $(CFLAGS) $(OPT_FLAG) $(CP).o -o $(CP)_$(BLOCK)
time: cp
		./$(CP)_$(BLOCK) $(TEST1) >>  pomiar_zad_2.txt
		./$(CP)_$(BLOCK) $(TEST2) >>  pomiar_zad_2.txt
		./$(CP)_$(BLOCK) $(TEST3) >>  pomiar_zad_2.txt
		./$(CP)_$(BLOCK) $(CP)_$(BLOCK) tmp1 >/dev/null ;./$(CP)_$(BLOCK) $(TEST5) >/dev/null ; diff -s $(CP)_$(BLOCK) tmp2 >>  pomiar_zad_2.txt


clean:
		rm -f *.o $(CP)_1 $(CP)_1024 rev?.txt ? valgrind-out.txt rev? tmp?
