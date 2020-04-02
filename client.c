#include "network_board.h"
#define PORT 8080

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char * serverAddr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if (argc <2) { //checks that user input server ip address
      printf("Missing server ip address\n");
      exit(1);
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    serverAddr = argv[1];

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverAddr, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // checks if client has connected to the server socket
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // send message to server to test connection
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n\n",buffer );

    // builds the board for the client then moves onto server's board
    build_board_client(sock);
    memset(buffer,0,strlen(buffer));
    valread = read( sock , buffer, 1024);
    printf("%s\n\n",buffer );

    // while loop used for running the game
    while(strcmp(buffer,"Done") != 0) { //If game over after client's turn
      memset(buffer,0,strlen(buffer));
      valread = read( sock , buffer, 1024);
      if(strcmp(buffer,"Done") == 0) { //If game over after server's turn
        break;
      }
      memset(buffer,0,strlen(buffer));
      valread = read( sock , buffer, 1024);
      printf("%s\n\n",buffer );
      memset(buffer,0,strlen(buffer));
      valread = read( sock , buffer, 1024);
      printf("Your Guesses:\n");
      printf("%s\n",buffer );
      memset(buffer,0,strlen(buffer));
      valread = read( sock , buffer, 1024);
      printf("Your Board:\n");
      printf("%s\n",buffer );
      make_guess_client(sock);
      memset(buffer,0,strlen(buffer));
      valread = read( sock , buffer, 1024);
    }
    //print winnter
    memset(buffer,0,strlen(buffer));
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}
