#GTK = 'pkg-config --cflags gtk+-3.0' 'pkg-config --libs gtk+-3.0'
C = clang
OPTIONSO = -Wall -lpthread -o
SHARED_FUNCTIONSC = utilities.c sendReceive.c connect.c
SHARED_FUNCTIONSO = utilities.o sendReceive.o connect.o

all: clean client server

client: client.o $(SHARED_FUNCTIONSO)
	$(C) $(OPTIONSO) client client.c $(SHARED_FUNCTIONSC)

server: server.o $(SHARED_FUNCTIONSO)
	$(C) $(OPTIONSO) server server.c $(SHARED_FUNCTIONSC)

client.o server.o $(SHARED_FUNCTIONSO): Header.h
	
clean:
	rm -rf *.o
	rm -rf *.txt

