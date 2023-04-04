CC=gcc
CFLAGS=-Wall
SI=signals_fork
SE=signals_exec

all: fork exec test

fork: $(SI).c
	$(CC) $(CFLAGS) -c $(SI).c
	$(CC) $(CFLAGS) $(SI).o -o $(SI)

exec: $(SE).c
	$(CC) $(CFLAGS) -c $(SE).c
	$(CC) $(CFLAGS) $(SE).o -o $(SE)

test: fork exec
	@echo "\nIGNORE"  > out.txt
	./$(SI) ignore >> out.txt
	@echo "" >> out.txt
	./$(SE) ignore >> out.txt
	@echo "\nHANDLER" >> out.txt
	./$(SI) handler >> out.txt
	@echo "\nMASK" >> out.txt
	./$(SI) mask >> out.txt
	@echo "" >> out.txt
	./$(SE) mask >> out.txt
	@echo "\nPENDING" >> out.txt
	./$(SI) pending >> out.txt
	@echo "" >> out.txt
	./$(SE) pending >> out.txt

clean:
	rm -f *.o $(SI) $(SE) out.txt