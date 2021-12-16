journal: journal.o
	gcc -Wall -o journal journal.o

journal.o: journal.c
	gcc -Wall -c journal.c

clean:
	rm -rf *.o
