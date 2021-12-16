C = gcc
OPTIONSO = -lm -Wall -std=c99 -o
FUNCTIONSO = generateSamples.o writeSamples.o createHistogram.o meanAndStdDev.o  

all: main

main: main.o $(FUNCTIONSO)
	$(C) $(OPTIONSO) Histogram main.o $(FUNCTIONSO)

main.o $(FUNCTIONSO): Header.h

clean:
	rm -rf *.o
	rm -rf *.txt
