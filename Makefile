CC = gcc
FLAGS = -Wall -std=c99
OBJECTS = MemAlloc.o Memory_Processing.o Algorithms.o

all: MemAlloc

MemAlloc: $(OBJECTS)
	$(CC) $(FLAGS) -o MemAlloc $(OBJECTS)

MemAlloc.o: MemAlloc.c
	$(CC) -c $(FLAGS) MemAlloc.c

Memory_Processing.o: Memory_Processing.c
	$(CC) -c $(FLAGS) Memory_Processing.c

Algorithms.o: Algorithms.c
	$(CC) -c $(FLAGS) Algorithms.c

clean:
	rm *.o

# Make with small sample numbers for testing.
x:
	make clean
	make all
	./MemAlloc 100 50 12.5 3.5

# Make with scenario 1 sample numbers.
x1: 
	make clean
	make all
	./MemAlloc 1000 16777216 1048576 262144.0

# Make with scenario 2 sample numbers.
x2:
	make clean
	make all
	./MemAlloc 1000 16777216 4194304 1363148.8

# Make with scenario 3 sample numbers.
x3:
	make clean
	make all
	./MemAlloc 5000 1073741824 1048576 262144.0

# Make with scenario 4 sample numbers.
x4:
	make clean
	make all
	./MemAlloc 500 1073741824 268435456 67108864.0