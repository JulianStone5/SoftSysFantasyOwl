#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define CLIENT_NUM 2

int main(int argc, char const *argv[])
{
    // server_fd is master socket
    int server_fd, new_socket, valread, client_socket[CLIENT_NUM], max_clients = CLIENT_NUM;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    fd_set socket_set;

    // Creating socket file descriptor
    // socket descriptor uses IP v 4 with TCP connection
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    // Forcefully attaching socket to the port 8080, creating a master socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    // socket type
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // binding socket to the port 8080
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

    //try to specify maximum of 2 pending connections for the master socket
    if (listen(master_socket, 2) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    // valread = read( new_socket , buffer, 1024);
    // printf("%s\n",buffer );
    // send(new_socket , hello , strlen(hello) , 0 );
    // printf("Hello message sent\n");

    while (1)
    {
      // makes sure that the socket set is empty
      FD_zero(&socket_set);
      // adds master socket to set
      FD_SET(master_socket, &socket_set);

      max_sd = server_fd;

      for ( i = 0 ; i < max_clients ; i++)
      {
          //socket descriptor
          sd = client_socket[i];

          //if valid socket descriptor then add to read list
          if(sd > 0)
              FD_SET( sd , &socket_set);

          //finding the highest file descriptor for use in the select function
          if(sd > max_sd)
              max_sd = sd;
      }
      AFK_Check = select( max_sd + 1 , &socket_set , NULL , NULL , NULL);
      if ((AFK_Check < 0) && (errno!=EINTR))
        {
            printf("select error");
        }
    }
    return 0;
}
