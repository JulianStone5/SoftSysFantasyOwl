#include "board.h"

int rows = 9;
int cols = 11;

void delay(int milsec){
  clock_t startTime = clock();
  while(clock() < (startTime + milsec));
}

/*
Make_board creates and populates a 9x11 board with zeros
*/
void make_board(int board[rows][cols]) {
  int i, j;
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      board[i][j] = 0;
    }
  }
}

/*
This function prints the entire board.
*/
void print_board(int board[rows][cols]) {
  int i,j;
  printf("  ");
  for(j = 0; j < cols; j++) {
    printf("  %c ", (char)(j+'A'));
  }
  printf(" \n");
  for(i = 0; i < rows; i++) {
    printf("%d ", i+1);
    for(j = 0; j < cols; j++) {
      int val = board[i][j];
      if(val == 0) {
        printf("| ~ ");
      } else if(val == -1) {
        printf("| X ");
      } else if(val == -2) {
        printf("| O ");
      } else {
        printf("| %d ",val);
      }
    }
    printf("|\n");
  }
}

void getBoardString(int board[rows][cols], char board_str[1000]) {
  strcat(board_str, "  ");
  int i,j;
  char temp[5];
  for(j = 0; j < cols; j++) {
    sprintf(temp,"  %c ", (char)(j+'A'));
    strcat(board_str, temp);
  }
  strcat(board_str, " \n");
  for(i = 0; i < rows; i++) {
    sprintf(temp,"%d ",i+1);
    strcat(board_str, temp);
    for(j = 0; j < cols; j++) {
      int val = board[i][j];
      if(val == 0) {
        strcat(board_str, "| ~ ");
      } else if(val == -1) {
        strcat(board_str, "| X ");
      } else if(val == -2) {
        strcat(board_str, "| 0 ");
      } else {
        sprintf(temp,"| %d ",val);
        strcat(board_str, temp);
      }
    }
    strcat(board_str, "|\n");
  }
}

/*
Converts ships number label to ship size
*/
int get_size(int ship) {
  switch(ship) {
    case 1:
      return 2;
      break;
    case 2:
      return 3;
      break;
    case 3:
      return 3;
      break;
    case 4:
      return 4;
      break;
    case 5:
      return 5;
      break;
  }
}

void make_ship_counts(int ship_counts[5]) {
  int i;
  for(i = 0; i < 5; i++) {
    ship_counts[i] = get_size(i+1);
  }
}

/*
Add a ship to a board given its label, start pos, and direction
*/
void add_ship(int board[rows][cols], int ship, int sX, int sY, int dir) {
  int i, j;
  int right = (dir == 1) ? 1 : 0;
  int down = (dir == 2) ? 1 : 0;
  int ship_size = get_size(ship);
  for(i = sY; i < sY+down*ship_size+right; i++) {
    for(j = sX; j < sX+right*ship_size+down; j++) {
      board[i][j] = ship;
    }
  }
}

/*
Get user input to pick a ship's direction
*/
int getDir(char * input) {
  printf("Direction? Right (1) or Down (2): ");
  fgets(input, 5, stdin);
  int dir = atoi(input);
  while(dir != 1 && dir != 2) {
    printf("Invalid input\n");
    printf("Direction? Right (1) or Down (2): ");
    fgets(input, 5, stdin);
    dir = atoi(input);
  }
  return dir;
}

int getDir_server(char * input, int new_socket) {
  delay(1000);
  char temp[50] = "Direction? Right (1) or Down (2): ";
  send(new_socket, temp, strlen(temp),0);
  int valread = read( new_socket , input, 5);
  int dir = atoi(input);
  while(dir != 1 && dir != 2) {
    sprintf(temp, "%s","Invalid input\nDirection? Right (1) or Down (2): ");
    send(new_socket, temp, strlen(temp),0);
    memset(input,0,strlen(input));
    valread = read( new_socket , input, 5);
    sprintf(temp, "%c", input[0]);
    dir = atoi(temp);
  }
  send(new_socket , "Done" , strlen("Done") , 0 );
  return dir;
}

void getDir_client(int sock) {
  char b[1024];
  int valread = read( sock , b, 1024);
  while(strcmp(b,"Done") != 0) {
    printf("%s\n",b);
    char input[100];
    fgets(input,100,stdin);
    send(sock,input,strlen(input),0);
    memset(b,0,strlen(b));
    valread = read( sock , b, 1024);
  }
}

/*
Detect if a new ship would be colliding with existing ships
*/
int isColliding(int board[rows][cols], int s[2], int ship_size, int dir) {
  int i, j;
  int right = (dir == 1) ? 1 : 0;
  int down = (dir == 2) ? 1 : 0;
  for(i = s[1]; i < s[1]+down*ship_size+right; i++) {
    for(j = s[0]; j < s[0]+right*ship_size+down; j++) {
      if(board[i][j] > 0) {
        return 1;
      }
    }
  }
  return 0;
}

/*
Get user input to pick a ship's starting point
*/
void getStart(int board[rows][cols],char * input, int s[2],int ship_size, int dir) {
  printf("Starting Coordinate? Options A1-K9: ");
  fgets(input, 5, stdin);
  s[0] = input[0]-'A';
  s[1] = input[1]-'1';
  int right = (dir == 1) ? 1 : 0;
  int down = (dir == 2) ? 1 : 0;
  int valX = ((s[0] <= cols - right*ship_size) && (s[0] >= 0)) ? 1 : 0;
  int valY = ((s[1] <= rows - down*ship_size) && (s[1] >= 0)) ? 1 : 0;
  while(!valX || !valY || isColliding(board,s, ship_size, dir)) {
    printf("Invalid input\n");
    printf("Starting Coordinate? Options A1-K9: ");
    fgets(input, 5, stdin);
    s[0] = input[0]-'A';
    s[1] = input[1]-'1';
    valX = ((s[0] <= cols - right*ship_size) && (s[0] >= 0)) ? 1 : 0;
    valY = ((s[1] <= rows - down*ship_size) && (s[1] >= 0)) ? 1 : 0;
  }
}

void getStart_server(int board[rows][cols],char * input, int s[2],int ship_size, int dir, int new_socket) {
  delay(1000);
  char temp[100] = "Starting Coordinate? Options A1-K9: ";
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
    send(new_socket, temp, strlen(temp),0);
    memset(input,0,strlen(input));
    valread = read( new_socket , input, 5);
    s[0] = input[0]-'A';
    s[1] = input[1]-'1';
    valX = ((s[0] <= cols - right*ship_size) && (s[0] >= 0)) ? 1 : 0;
    valY = ((s[1] <= rows - down*ship_size) && (s[1] >= 0)) ? 1 : 0;
  }
  send(new_socket , "Done" , strlen("Done") , 0 );
}

/*
Get user input to build a starting board
*/
void build_board(int board[rows][cols]) {
  make_board(board);
  int i;
  char input[5];
  printf("Generating board...\n\n");
  for(i = 1; i <= 5; i++) {
    print_board(board);
    printf("\n");
    int ship_size = get_size(i);
    printf("Let's place Ship %d of size %d...\n", i, ship_size);
    int dir = getDir(input);
    int s[2];
    getStart(board,input,s,ship_size,dir);
    add_ship(board,i,s[0],s[1],dir);
    printf("\n");
  }
  print_board(board);
  printf("Done. Board Generated.\n");
}

void build_board_server(int board[rows][cols], int new_socket) {
  make_board(board);
  int i;
  char input[5];
  char temp[100];
  delay(1000);
  sprintf(temp,"%s","Generating board...\n\n");
  send(new_socket , temp , strlen(temp) , 0 );
  for(i = 1; i <= 5; i++) {
    // char board_str[100];
    // getBoardString(board,board_str);
    // strcat(board_str,"\n");
    // send(new_socket,board_str,strlen(board_str),0);
    // delay(1000);
    int ship_size = get_size(i);
    // sprintf(temp,"Let's place Ship %d of size %d...\n", i, ship_size);
    // send(new_socket,temp,strlen(temp),0);
    // delay(1000);
    int dir = getDir_server(input,new_socket);
    int s[2];
    getStart_server(board,input,s,ship_size,dir, new_socket);
    add_ship(board,i,s[0],s[1],dir);
  }
  char * board_str = malloc(1000* sizeof(char));
  getBoardString(board,board_str);
  delay(1000);
  send(new_socket, board_str, strlen(board_str),0);
  //print_board(board);
  //printf("Done. Board Generated.\n");
}

void build_board_client(int sock) {
  char b[1024];
  int valread = read( sock , b, 1024);
  printf("%s",b);
  int i;
  for(i = 1; i <= 5; i++) {
    // memset(b,0,strlen(b));
    // valread = read( sock , b, 1024);
    // printf("%s",b);
    // //printf("hi\n");
    // memset(b,0,strlen(b));
    // valread = read( sock , b, 1024);
    // printf("%s",b);
    // //printf("bye\n");
    getDir_client(sock);
    getDir_client(sock);
    printf("\n");
  }
  memset(b,0,strlen(b));
  valread = read( sock , b, 1024);
  b[480] = '\0';
  printf("%s\n",b);
  printf("%ld\n",strlen(b));
  printf("Done. Board Generated.\n");
}

void make_guess(int board[rows][cols], int guess[rows][cols], int ship_counts[5]) {
  int s[2];
  char input[5];
  printf("Guess? Options A1-K9: ");
  fgets(input, 5, stdin);
  s[0] = input[0]-'A';
  s[1] = input[1]-'1';
  int valX = ((s[0] < cols) && (s[0] >= 0)) ? 1 : 0;
  int valY = ((s[1] < rows) && (s[1] >= 0)) ? 1 : 0;
  while(!valX || !valY) {
    printf("Invalid Input");
    printf("Guess? Options A1-K9: ");
    fgets(input, 5, stdin);
    s[0] = input[0]-'A';
    s[1] = input[1]-'1';
    int valX = ((s[0] < cols) && (s[0] >= 0)) ? 1 : 0;
    int valY = ((s[1] < rows) && (s[1] >= 0)) ? 1 : 0;
  }
  if(isColliding(board,s,1,1)) {
    printf("Hit!\n");
    ship_counts[board[s[1]][s[0]]-1]--;
    guess[s[1]][s[0]] = -1;
    board[s[1]][s[0]] = -1;
  } else {
    printf("Miss!\n");
    guess[s[1]][s[0]] = -2;
  }
}

int hasLost(int ship_counts[5]) {
  int i;
  for(i = 0; i < 5; i++) {
    if(ship_counts[i] != 0) {
      return 0;
    }
  }
  return 1;
}
