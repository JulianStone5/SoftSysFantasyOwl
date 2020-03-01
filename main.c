#include "board.h"

typedef struct {
  int board[9][11];
  int guess[9][11];
  int ship_counts[5];
} Player;

/*
The main function executes the above functions in
order to create and print a board.
*/
int main() {
  Player *p1 = malloc(sizeof(Player));
  Player *p2 = malloc(sizeof(Player));
  make_board(p1->guess);
  make_board(p2->guess);
  make_ship_counts(p1->ship_counts);
  make_ship_counts(p2->ship_counts);
  build_board(p1->board);
  build_board(p1->board);
  make_guess(p1->board,p2->guess,p1->ship_counts);
  //print_board(board);
  return 0;
}
