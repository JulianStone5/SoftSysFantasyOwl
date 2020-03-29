#include "network_board.h"
#define PORT 8080

typedef struct {
  int board[9][11];
  int guess[9][11];
  int ship_counts[5];
} Player;

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    // socket descriptor uses IP v 4 with TCP connection
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");

    Player *client = malloc(sizeof(Player));
    Player *server = malloc(sizeof(Player));
    make_ship_counts(client->ship_counts);
    make_ship_counts(server->ship_counts);
    make_board(client->guess);
    make_board(server->guess);

    printf("Waiting for Player 1 Board Generation\n");
    build_board_server(client->board,new_socket);
    usleep(wait_time);
    sprintf(buffer,"%s","Waiting for Player 2 Board Generation");
    send(new_socket,buffer,strlen(buffer),0);
    build_board(server->board);

    char * board_str = malloc(1000* sizeof(char));
    int playerTurn = 0;
    while(!hasLost(client->ship_counts) && !hasLost(server->ship_counts)) {
      usleep(wait_time);
      send(new_socket,"Nope",strlen("Nope"),0);
      if(!playerTurn) {
        printf("Player 1's Turn\n");
        usleep(wait_time);
        send(new_socket,"Player 1's Turn", strlen("Player 1's Turn"),0);
        memset(board_str, 0, strlen(board_str));
        getBoardString(client->guess,board_str);
        usleep(wait_time);
        send(new_socket, board_str, strlen(board_str),0);
        memset(board_str, 0, strlen(board_str));
        getBoardString(client->board,board_str);
        usleep(wait_time);
        send(new_socket, board_str, strlen(board_str),0);
        make_guess_server(server->board, client->guess, server->ship_counts,new_socket);
        playerTurn = 1;
      } else {
        printf("Player 2's Turn\n");
        print_board(server->guess);
        printf("\n");
        print_board(server->board);
        make_guess(client->board, server->guess, client->ship_counts);
        playerTurn = 0;
      }
    }
    usleep(wait_time);
    send(new_socket,"Done",strlen("Done"),0);
    usleep(wait_time);
    if(!playerTurn) {
      printf("Player 2 Wins!\n");
      send(new_socket,"Player 2 Wins!",strlen("Player 2 Wins!"),0);
    } else {
      printf("Player 1 Wins!\n");
      send(new_socket,"Player 1 Wins!",strlen("Player 1 Wins!"),0);
    }
    return 0;
}
