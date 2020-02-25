#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Make_board creates and populates a 9x11 board with zeros
*/
void make_board(int *board, int rows, int cols) {
  int i, j;
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      *(board+i*cols+j) = 0;
    }
  }
}

/*
This function prints the entire board.
*/
void print_board(int *board, int rows, int cols) {
  int i,j;
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j++) {
      char c[2];
      sprintf(c, "%d",*(board+i*cols+j));
      if(c[0] == '0') {
        c[0] = '~';
      }
      printf("| %s ",c);
    }
    printf("|\n");
  }
}

int get_type(int ship) {
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

void add_ship(int *board, int rows, int cols, int ship, int sX, int sY, int dir) {
  int i, j;
  int right = (dir == 1) ? 1 : 0;
  int down = (dir == 2) ? 1 : 0;
  int ship_type = get_type(ship);
  for(i = sY; i < sY+down*ship_type+right; i++) {
    for(j = sX; j < sX+right*ship_type+down; j++) {
      *(board+i*cols+j) = ship;
    }
  }
}

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

void getStart(int * s, char * input, int dir, int ship_type, int rows, int cols) {
  printf("Starting Coordinate? Options A1-K9: ");
  fgets(input, 5, stdin);
  s[0] = input[0]-'A';
  s[1] = input[1]-'1';
  int right = (dir == 1) ? 1 : 0;
  int down = (dir == 2) ? 1 : 0;
  int valX = (s[0] < rows - right*ship_type);
}

void build_board(int *board, int rows, int cols) {
  make_board(board,rows,cols);
  int i;
  char input[5];
  for(i = 1; i <= 5; i++) {
    int ship_type = get_type(i);
    printf("Let's place Ship %d of size %d...\n", i, ship_type);
    int dir = getDir(input);
    int s[2];
    getStart(s,input, dir, ship_type, rows, cols);
    add_ship(board,rows,cols,i,s[0],s[1],dir);
    printf("\n");
    print_board(board,rows,cols);
    printf("\n");
  }
}

/*
The main function executes the above functions in
order to create and print a board.
*/
int main() {
  int rows = 9, cols = 11;
  int *board = (int *)malloc(rows*cols*sizeof(int));
  build_board(board, rows, cols);
  print_board(board, rows, cols);
  return 0;
}
