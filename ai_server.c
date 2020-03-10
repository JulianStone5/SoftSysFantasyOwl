#include "board.h"
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

    char * input = malloc(5*sizeof(char));
    int a = getDir_server(input, new_socket);
    // Player *p1 = malloc(sizeof(Player));
    // Player *p2 = malloc(sizeof(Player));
    // make_board(p1->guess);
    // make_board(p2->guess);
    // make_ship_counts(p1->ship_counts);
    // make_ship_counts(p2->ship_counts);
    //
    // char * board_str = malloc(1000* sizeof(char));
    // getBoardString(p1->guess,board_str);
    // printf("%s",board_str);
    //send(new_socket, board_str, strlen(board_str),0);
    return 0;
}
