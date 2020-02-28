#include "board.h"

/*
The main function executes the above functions in
order to create and print a board.
*/
int main() {
  int board[rows][cols];
  int guess[rows][cols];
  //make_board(guess);
  build_board(board);
  //make_guess(board,guess);
  //print_board(board);
  return 0;
}
