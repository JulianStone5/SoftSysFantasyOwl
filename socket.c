#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define SA struct sockaddr


/* untested / unintegrated */
void person2client(int socket){
  char buffer[80];
  int n;
  while(1){
    /* fill all spaces in buffer with 0 values,
    and then read the contents of socket and
    write them to buffer */
    bzero(buffer, 80);
    read(socket, buffer, sizeof(buffer));
    /* reset buffer with zeros */
    bzero(buffer, 80);
    n = 0;
    while ((buffer[n+1]) = getchar()) != '\n'){
      write(socket, buffer, sizeof(buffer));
      if (strncmp("exit", buffer, 4)){
        printf("Exiting Server \n");
        break;
      }
    }
  }
}
