CC = gcc
CFLAGS = -g -Wall -Wimplicit-function-declaration

all: server client

server: server.c
	$(CC) $(CFLAGS) -o $@ $^

client: client.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm -f *.o server client 
