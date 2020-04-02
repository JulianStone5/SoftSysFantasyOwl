#include "board.h"

int rows = 9;
int cols = 11;

/*
Make_board creates and populates a 9x11 board with zeros

int board: the number of rows and columns to make the board (9x11 in this case)
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

int board: The number of rows and columns of the board we're printing (9x11)
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

/*
Saves the board state as a string, useful for communication between terminals

int board: the size of the board (9x11)
char board_str[1000]: used to house the board state as a string
*/
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

int ship: the ship number

returns the value that represents the size of the aforementioned ship number
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

/*
simple function to initialize ship ship counts

int ship_counts[5]: an integer array to fill with counts
*/
void make_ship_counts(int ship_counts[5]) {
  int i;
  for(i = 0; i < 5; i++) {
    ship_counts[i] = get_size(i+1);
  }
}

/*
Add a ship to a board given its label, start pos, and direction

int board: a 9x11 two dimensional array
int ship: the ship number of the ship in question
int sX: starting x position
int sY: starting y position
int dir: 1 or 2 that determines whether the ship is facing right or down
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

char * input: pointer to a character array of user input for ship direction

returns an integer representing the direction the ship is facing, chosen by user
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

/*
Detect if a new ship would be colliding with existing ships

int board: two dimensional integer array that holds a 9x11 board
int s[2]: the starting index of the ship
int ship_size: size of the ship
int dir: direction of the ship

returns either 0 or 1, depending on whether the ship has collided
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

int board: two dimensional integer array that stores a 9x11 board
char * input: pointer to user input character array
int s[2]: starting index of ship
int ship_size: size of the ship in question
int dir: direction of the ship
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

/*
Get user input to build a starting board

int board: two dimensional integer array that houses a 9x11 board
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

/*
allows the user to make a guess and checks to see the validity and
outcome of the guess

int board: two dimensional integer array that houses a 9x11 board
int guess: the index the user guesses
int ship_counts: the total ship count left
*/
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
    valX = ((s[0] < cols) && (s[0] >= 0)) ? 1 : 0;
    valY = ((s[1] < rows) && (s[1] >= 0)) ? 1 : 0;
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

/*
looks at the board to see if all ships have been sunk

int ship_count[5]: takes an array that represents the health of the five ships

returns 1 if player has lost, else return 0
*/
int hasLost(int ship_counts[5]) {
  int i;
  for(i = 0; i < 5; i++) {
    if(ship_counts[i] != 0) {
      return 0;
    }
  }
  return 1;
}
