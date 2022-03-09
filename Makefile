CC = gcc
FLAGS = -Wall -std=c99
FUNCTIONSO = main.o Algorithms.o MemoryProcessing.o PrintUtilities.o
FUNCTIONSC = main.c Algorithms.c MemoryProcessing.c PrintUtilities.c

all: MemoryAllocationSimulator

MemoryAllocationSimulator: $(FUNCTIONSO)
	$(CC) $(FLAGS) -o MemoryAllocationSimulator $(FUNCTIONSO)

$(FUNCTIONSO): $(FUNCTIONSC)
	$(CC) -c $(FLAGS) $(FUNCTIONSC)

clean:
	rm *.o

# Make with small sample numbers for testing.
# Numbers represent the following: (number of iterations, memory size, mean, std dev)
test1:
	make clean
	make all
	./MemoryAllocationSimulator 10 200 26 6.0 #10 100 25 7.
	# Num Iterations: 10 | Memory Size: 100 | Mean: 25 | StdDev: 7

test2:
	make clean
	make all
	./MemoryAllocationSimulator 100 200 104857 26214.0
	# Num Iterations: 100 | Memory Size: 200 | Mean: 104857 | StdDev: 26214.0

test3:
	make clean
	make all
	./MemoryAllocationSimulator 10000 5000 419430 136314.8
	# Num Iterations: 10000 | Memory Size: 5000 | Mean: 419430 | StdDev: 136314.8

# Make with larger scenario numbers for real implementation.
# Numbers represent the following: (number of iterations, memory size, mean, std dev)
scene1:
	make clean
	make all
	./MemoryAllocationSimulator 1000 16777216 1048576 262144.0
	# Num Iterations: 1000 | Memory Size: 16777216 | Mean: 1048576 | StdDev: 262144.0

scene2:
	make clean
	make all
	./MemoryAllocationSimulator 1000 16777216 4194304 1363148.8
	# Num Iterations: 1000 | Memory Size: 16777216 | Mean: 4194304 | StdDev: 1363148.8

scene3:
	make clean
	make all
	./MemoryAllocationSimulator 500 1073741824 268435456 67108864.0
	# Num Iterations: 500 | Memory Size: 1073741824 | Mean: 268435456 | StdDev: 67108864.0

# TO USE, UNCOMMENT ALL BUT LAST LINE, ADD TABS, AND REMOVE ALL COLONS AFTER 'scene4:'.
# scene4:
# make clean:
# make all:
# ./MemoryAllocationSimulator 5000 1073741824 1048576 262144.0:
# Num Iterations: 5000 | Memory Size: 1073741824 | Mean: 1048576 | StdDev: 262144.0:
