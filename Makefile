#GTK = 'pkg-config --cflags gtk+-3.0' 'pkg-config --libs gtk+-3.0'

all: client server

client: client.o
	clang -Wall -lpthread -o client client.c

server: server.o
	clang -Wall -lpthread -o server server.c

clean:
	rm -rf *.o
	rm -rf *.txt

