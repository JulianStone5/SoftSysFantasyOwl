#include "network_board.h"

int wait_time = 10000;

/*
getDir_server() is used by the server file to communicate with the client to get
the desired direction of the ship to be placed. Will continually prompt the
client if the input is invalid

input: user input for desired direction
new_socket: socket connection of client

returns direction of the ship to be place (0 for right and 1 for down)
*/
int getDir_server(char * input, int new_socket) {
  usleep(wait_time);
  char *temp = malloc(50*sizeof(char));
  sprintf(temp,"%s","Direction? Right (1) or Down (2): ");
  send(new_socket, temp, strlen(temp),0);
  int valread = read( new_socket , input, 5);
  int dir = atoi(input);
  while(dir != 1 && dir != 2) { //Will continue asking as long as input is invalid
    sprintf(temp, "%s","Invalid input\nDirection? Right (1) or Down (2): ");
    usleep(wait_time);
    send(new_socket, temp, strlen(temp),0);
    memset(input,0,strlen(input));
    valread = read( new_socket , input, 5);
    sprintf(temp, "%c", input[0]);
    dir = atoi(temp); //Converts input into an integer
  }
  usleep(wait_time);
  send(new_socket , "Done" , strlen("Done") , 0 );
  return dir;
}

/*
getStart_server() is used by the server file to communicate with the client to get
the desired starting coordiante of the ship to be placed. Will continually ask
the client for a new input as long as the given starting coordinate is invalid.

board: board for ship to be placed on
input: user input for desired starting position
s: array for coordinates to be stored in
ship_size: size of the ship being placed
dir: direction of ship being placed
new_socket: socket connection of client
*/
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
  int valX = ((s[0] <= cols - right*ship_size) && (s[0] >= 0)) ? 1 : 0; //Boolean for if the x coor is valid
  int valY = ((s[1] <= rows - down*ship_size) && (s[1] >= 0)) ? 1 : 0; //Boolean for if the y coor is valid
  while(!valX || !valY || isColliding(board,s, ship_size, dir)) { //Will continue asking as long as input is invalid
    sprintf(temp, "%s","Invalid input\nDirection? Starting Coordinate? Options A1-K9: ");
    usleep(wait_time);
    send(new_socket, temp, strlen(temp),0);
    memset(input,0,strlen(input));
    valread = read( new_socket , input, 5);
    s[0] = input[0]-'A'; //Converting input into array indeces
    s[1] = input[1]-'1';
    valX = ((s[0] <= cols - right*ship_size) && (s[0] >= 0)) ? 1 : 0;
    valY = ((s[1] <= rows - down*ship_size) && (s[1] >= 0)) ? 1 : 0;
  }
  usleep(wait_time);
  send(new_socket , "Done" , strlen("Done") , 0 );
}

/*
getInfo() is used by the client to send info to the server when asked for it.
Functions used by the server have similar formatting, so this function is able
to work in conjunction with these functions to get inputs for the user and send
it to the server

sock: socket connection of server
*/
void getInfo(int sock) {
  char *b = malloc(1024*sizeof(char));
  int valread = read( sock , b, 1024);
  while(strcmp(b,"Done") != 0) { //Will continue as long as server is asking for info
    printf("%s",b);
    char input[5];
    fgets(input,5,stdin);
    usleep(wait_time);
    send(sock,input,strlen(input),0);
    memset(b,0,strlen(b));
    valread = read( sock , b, 1024);
  }
}

/*
build_board_server() conducts the server side sequence for placing ships on a
board. For each of five ships, the server will ask the client for inputs like
the direction and starting coordiante of the ship and will place each of them
in the correct place.

board: array representing the board that the ships will be placed on
new_socket: socket connection of client
*/
void build_board_server(int board[rows][cols], int new_socket) {
  make_board(board);
  int i;
  char *input = malloc(5*sizeof(char));
  char *temp = malloc(100*sizeof(char));
  usleep(wait_time);
  sprintf(temp,"%s","Generating board...\n\n");
  send(new_socket , temp , strlen(temp) , 0 );
  char *board_str = malloc(1000*sizeof(char));
  for(i = 1; i <= 5; i++) { //Runs for each of the five ships
    memset(board_str,0,strlen(board_str));
    getBoardString(board,board_str);
    usleep(wait_time);
    send(new_socket,board_str,strlen(board_str),0);
    int ship_size = get_size(i);
    sprintf(temp,"Let's place Ship %d of size %d...\n", i, ship_size);
    usleep(wait_time);
    send(new_socket,temp,strlen(temp),0);
    int dir = getDir_server(input,new_socket); //Gets the desired direction
    int s[2];
    getStart_server(board,input,s,ship_size,dir, new_socket); //Gets desired starting coordinate
    add_ship(board,i,s[0],s[1],dir);
  }
  memset(board_str,0,strlen(board_str));
  getBoardString(board,board_str);
  usleep(wait_time);
  send(new_socket, board_str, strlen(board_str),0);
}

/*
build_board_client() conducts the client side sequence for placing ships on a
board. For each of five ships, the client will give the server information
regarding chacteristics like the direction and starting coordinate

sock: socket connection of server
*/
void build_board_client(int sock) {
  char *b = malloc(1024*sizeof(char));
  int valread = read( sock , b, 1024);
  printf("%s",b);
  int i;
  for(i = 1; i <= 5; i++) {//Runs for each of five ships
    memset(b,0,strlen(b));
    valread = read( sock , b, 1024);
    printf("%s",b);
    memset(b,0,strlen(b));
    valread = read( sock , b, 1024);
    printf("%s",b);
    getInfo(sock); //Getting direction input
    getInfo(sock); //Getting starting coordinate input
    printf("\n");
  }
  memset(b,0,strlen(b));
  valread = read( sock , b, 1024);
  b[480] = '\0';
  printf("%s\n",b);
  printf("Done. Board Generated.\n");
}

/*
make_guess_server() conducts the server side sequence of making a guess against
the opponent's board. It will ask the client for a coordinate and then will
inform the client if the guess was a hit or a miss

board: array representing board being guessed against
guess: array representing guess board of player guessing
ship_counts: array representing spaces of each ship remaining for opponents ships
new_socket: socket connection of client
*/
void make_guess_server(int board[rows][cols], int guess[rows][cols], int ship_counts[5], int new_socket) {
  int s[2];
  char *input = malloc(5*sizeof(char));
  char *temp = malloc(100*sizeof(char));
  sprintf(temp,"%s","Guess? Options A1-K9: ");
  usleep(wait_time);
  send(new_socket, temp, strlen(temp),0);
  int valread = read( new_socket , input, 5);
  s[0] = input[0]-'A';
  s[1] = input[1]-'1';
  int valX = ((s[0] < cols) && (s[0] >= 0)) ? 1 : 0; //Boolean for if the x coor is valid
  int valY = ((s[1] < rows) && (s[1] >= 0)) ? 1 : 0; //Boolean for if the y coor is valid
  while(!valX || !valY) { //Will continue as long as input isn't valid
    sprintf(temp,"%s","Invalid Input\nGuess? Options A1-K9: ");
    usleep(wait_time);
    send(new_socket, temp, strlen(temp),0);
    memset(input,0,strlen(input));
    int valread = read( new_socket , input, 5);
    s[0] = input[0]-'A'; //Converts input into array indeces
    s[1] = input[1]-'1';
    valX = ((s[0] < cols) && (s[0] >= 0)) ? 1 : 0;
    valY = ((s[1] < rows) && (s[1] >= 0)) ? 1 : 0;
  }
  usleep(wait_time);
  send(new_socket , "Done" , strlen("Done") , 0 );
  if(isColliding(board,s,1,1)) { //If the guess is a hit
    sprintf(temp,"%s","Hit!\n");
    ship_counts[board[s[1]][s[0]]-1]--;
    guess[s[1]][s[0]] = -1;
    board[s[1]][s[0]] = -1;
  } else { //If the guess is a miss
    sprintf(temp,"%s","Miss!\n");
    guess[s[1]][s[0]] = -2;
  }
  usleep(wait_time);
  send(new_socket, temp, strlen(temp),0);
}

/*
make_guess_client() conducts the client side sequence for making a guess against
the opponent's board. It will send info to the server than will read if it was a
hit or a miss.

sock: socket connect of server
*/
void make_guess_client(int sock) {
  getInfo(sock); //Gets guess input from user
  char *b = malloc(1024*sizeof(char));
  int valread = read( sock , b, 1024); //Reads if it was a hit or miss
  printf("%s",b);
}
