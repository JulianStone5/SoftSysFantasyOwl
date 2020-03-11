// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <string.h>
#include "board.h"
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

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    
    getDir_client(sock);
    return 0;
}
