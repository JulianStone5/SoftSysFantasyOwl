main: main.o board.o
	gcc main.o board.o -o main
main.o: main.c board.h
	gcc -c main.c
board.o: board.c board.h
	gcc -c board.c
