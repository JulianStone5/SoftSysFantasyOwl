all: main ai_server client #server

main: main.o board.o
	gcc main.o board.o -o main
main.o: main.c board.h
	gcc -c main.c
board.o: board.c board.h
	gcc -c board.c
# server: server.c
# 	gcc server.c -o server
client: client.c
	gcc client.c -o client
ai_server: ai_server.c
	gcc ai_server.c -o ai_server
