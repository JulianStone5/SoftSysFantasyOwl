#include "network_board.h"

int wait_time = 10000;

int getDir_server(char * input, int new_socket) {
  usleep(wait_time);
  char *temp = malloc(50*sizeof(char));
  sprintf(temp,"%s","Direction? Right (1) or Down (2): ");
  send(new_socket, temp, strlen(temp),0);
  int valread = read( new_socket , input, 5);
  int dir = atoi(input);
  while(dir != 1 && dir != 2) {
    sprintf(temp, "%s","Invalid input\nDirection? Right (1) or Down (2): ");
    usleep(wait_time);
    send(new_socket, temp, strlen(temp),0);
    memset(input,0,strlen(input));
    valread = read( new_socket , input, 5);
    sprintf(temp, "%c", input[0]);
    dir = atoi(temp);
  }
  usleep(wait_time);
  send(new_socket , "Done" , strlen("Done") , 0 );
  return dir;
}

void getStart_server(int board[rows][cols],char * input, int s[2],int ship_size, int dir, int new_socket) {
  usleep(wait_time);
  char *temp = malloc(100*sizeof(char));
  sprintf(temp,"%s", "Starting Coordinate? Options A1-K9: ");
  send(new_socket, temp, strlen(temp),0);
  int valread = read( new_socket , input, 5);
  s[0] = input[0]-'A';
  s[1] = input[1]-'1';
  int right = (dir == 1) ? 1 : 0;
  int down = (dir == 2) ? 1 : 0;
  int valX = ((s[0] <= cols - right*ship_size) && (s[0] >= 0)) ? 1 : 0;
  int valY = ((s[1] <= rows - down*ship_size) && (s[1] >= 0)) ? 1 : 0;
  while(!valX || !valY || isColliding(board,s, ship_size, dir)) {
    sprintf(temp, "%s","Invalid input\nDirection? Starting Coordinate? Options A1-K9: ");
    usleep(wait_time);
    send(new_socket, temp, strlen(temp),0);
    memset(input,0,strlen(input));
    valread = read( new_socket , input, 5);
    s[0] = input[0]-'A';
    s[1] = input[1]-'1';
    valX = ((s[0] <= cols - right*ship_size) && (s[0] >= 0)) ? 1 : 0;
    valY = ((s[1] <= rows - down*ship_size) && (s[1] >= 0)) ? 1 : 0;
  }
  usleep(wait_time);
  send(new_socket , "Done" , strlen("Done") , 0 );
}

void getInfo(int sock) {
  char *b = malloc(1024*sizeof(char));
  int valread = read( sock , b, 1024);
  while(strcmp(b,"Done") != 0) {
    printf("%s",b);
    char input[5];
    fgets(input,5,stdin);
    usleep(wait_time);
    send(sock,input,strlen(input),0);
    memset(b,0,strlen(b));
    valread = read( sock , b, 1024);
  }
}

void build_board_server(int board[rows][cols], int new_socket) {
  make_board(board);
  int i;
  char *input = malloc(5*sizeof(char));
  char *temp = malloc(100*sizeof(char));
  //TODO: free malloc space
  usleep(wait_time);
  sprintf(temp,"%s","Generating board...\n\n");
  send(new_socket , temp , strlen(temp) , 0 );
  char *board_str = malloc(1000*sizeof(char));
  for(i = 1; i <= 5; i++) {
    memset(board_str,0,strlen(board_str));
    getBoardString(board,board_str);
    usleep(wait_time);
    send(new_socket,board_str,strlen(board_str),0);
    int ship_size = get_size(i);
    sprintf(temp,"Let's place Ship %d of size %d...\n", i, ship_size);
    usleep(wait_time);
    send(new_socket,temp,strlen(temp),0);
    int dir = getDir_server(input,new_socket);
    int s[2];
    getStart_server(board,input,s,ship_size,dir, new_socket);
    add_ship(board,i,s[0],s[1],dir);
  }
  memset(board_str,0,strlen(board_str));
  getBoardString(board,board_str);
  usleep(wait_time);
  send(new_socket, board_str, strlen(board_str),0);
}

void build_board_client(int sock) {
  char *b = malloc(1024*sizeof(char));
  int valread = read( sock , b, 1024);
  printf("%s",b);
  int i;
  for(i = 1; i <= 5; i++) {
    memset(b,0,strlen(b));
    valread = read( sock , b, 1024);
    printf("%s",b);
    memset(b,0,strlen(b));
    valread = read( sock , b, 1024);
    printf("%s",b);
    getInfo(sock);
    getInfo(sock);
    printf("\n");
  }
  memset(b,0,strlen(b));
  valread = read( sock , b, 1024);
  b[480] = '\0';
  printf("%s\n",b);
  printf("Done. Board Generated.\n");
}

void make_guess_server(int board[rows][cols], int guess[rows][cols], int ship_counts[5], int new_socket) {
  int s[2];
  char *input = malloc(5*sizeof(char));
  char *temp = malloc(100*sizeof(char));
  //TODO:   remember to free mallocked space
  sprintf(temp,"%s","Guess? Options A1-K9: ");
  usleep(wait_time);
  send(new_socket, temp, strlen(temp),0);
  int valread = read( new_socket , input, 5);
  s[0] = input[0]-'A';
  s[1] = input[1]-'1';
  int valX = ((s[0] < cols) && (s[0] >= 0)) ? 1 : 0;
  int valY = ((s[1] < rows) && (s[1] >= 0)) ? 1 : 0;
  while(!valX || !valY) {
    sprintf(temp,"%s","Invalid Input\nGuess? Options A1-K9: ");
    usleep(wait_time);
    send(new_socket, temp, strlen(temp),0);
    memset(input,0,strlen(input));
    int valread = read( new_socket , input, 5);
    s[0] = input[0]-'A';
    s[1] = input[1]-'1';
    valX = ((s[0] < cols) && (s[0] >= 0)) ? 1 : 0;
    valY = ((s[1] < rows) && (s[1] >= 0)) ? 1 : 0;
  }
  usleep(wait_time);
  send(new_socket , "Done" , strlen("Done") , 0 );
  if(isColliding(board,s,1,1)) {
    sprintf(temp,"%s","Hit!\n");
    ship_counts[board[s[1]][s[0]]-1]--;
    guess[s[1]][s[0]] = -1;
    board[s[1]][s[0]] = -1;
  } else {
    sprintf(temp,"%s","Miss!\n");
    guess[s[1]][s[0]] = -2;
  }
  usleep(wait_time);
  send(new_socket, temp, strlen(temp),0);
}

void make_guess_client(int sock) {
  getInfo(sock);
  char *b = malloc(1024*sizeof(char));
  int valread = read( sock , b, 1024);
  printf("%s",b);
}
