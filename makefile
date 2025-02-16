CC := gcc

all: main

main: src/uelf.o main.o
	$(CC) src/uelf.o main.o -o main

src/uelf.o: src/uelf.c include/uelf.h
	$(CC) -Wall -W -pedantic -c src/uelf.c -o src/uelf.o

main.o: main.c include/uelf.h
	$(CC) -Wall -W -pedantic -c main.c -o main.o
clean:
	rm -rf src/*.o *.o main

