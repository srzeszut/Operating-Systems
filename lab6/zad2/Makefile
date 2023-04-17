CC=gcc
CFLAGS=-Wall
SE=server
CL=client


all: server client

server: $(SE).c
	$(CC) $(CFLAGS) -c $(SE).c
	$(CC) $(CFLAGS) $(SE).o -o $(SE)

client: $(CL).c
	$(CC) $(CFLAGS) -c $(CL).c
	$(CC) $(CFLAGS) $(CL).o -o $(CL)

test: server client
	gnome-terminal --command "./server"
	gnome-terminal --command "./client"
	gnome-terminal --command "./client"



clean:
	rm -f *.o $(CL) $(SE) out.txt