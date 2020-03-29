all: main server client

main: main.o board.o
	gcc main.o board.o -o main
main.o: main.c board.h
	gcc -c main.c
board.o: board.c board.h
	gcc -c board.c
network_board.o: network_board.c network_board.h board.h
	gcc -c network_board.c
server: server.o network_board.o board.o
	gcc server.o network_board.o board.o -o server
server.o: server.c network_board.h
	gcc -c server.c
client: client.o network_board.o board.o
	gcc client.o network_board.o board.o -o client
client.o: client.c network_board.h
	gcc -c client.c
