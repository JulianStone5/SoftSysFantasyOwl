#include "board.h"

/*
The main function executes the above functions in
order to create and print a board.
*/
int main() {
  int rows = 9, cols = 11;
  int *board = (int *)malloc(rows*cols*sizeof(int));
  build_board(board, rows, cols);
  return 0;
}
