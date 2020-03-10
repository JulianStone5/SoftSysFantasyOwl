all: main ai_client ai_server #client server

main: main.o board.o
	gcc main.o board.o -o main
main.o: main.c board.h
	gcc -c main.c
board.o: board.c board.h
	gcc -c board.c
# server: server.c
# 	gcc server.c -o server
# client: client.c
# 	gcc client.c -o client
ai_server: ai_server.o board.o
	gcc ai_server.o board.o -o ai_server
ai_server.o: ai_server.c board.h
	gcc -c ai_server.c
ai_client: ai_client.o board.o
	gcc ai_client.o board.o -o ai_client
ai_client.o: ai_client.c board.h
	gcc -c ai_client.c
