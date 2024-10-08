CC = gcc
AS = as
CFLAGS = -g -no-pie
LFLAGS = -lm

all: main bestFit

bestFit: main_bestFit.o bestFit.o 
	$(CC) $(CFLAGS) $(LFLAGS) -o bestFit main_bestFit.o bestFit.o

bestFit.o: bestFit.s
	$(AS) $(CFLAGS) -c bestFit.s -o bestFit.o

main: main.o memalloc.o
	$(CC) $(CFLAGS) $(LFLAGS) -o main main.o memalloc.o

memalloc.o: memalloc.s 
	$(AS) $(CFLAGS) -c memalloc.s -o memalloc.o

main.o: main.c memalloc.h
	$(CC) $(CFLAGS) -c main.c -o main.o

.PHONY: clean purge

clean:
	@rm -rf ./*.o

purge: clean
	@rm -rf main bestFit
