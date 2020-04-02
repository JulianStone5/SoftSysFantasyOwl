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
  // allocate memory for player1 (server side) and player2 (client)
  Player *p1 = malloc(sizeof(Player));
  Player *p2 = malloc(sizeof(Player));
  make_board(p1->guess);
  make_board(p2->guess);
  make_ship_counts(p1->ship_counts);
  make_ship_counts(p2->ship_counts);
  //place ships on boards
  build_board(p1->board);
  build_board(p2->board);
  //as long as someone hasn't lost, have a player make a guess
  int playerTurn = 0;
  while(!hasLost(p1->ship_counts) && !hasLost(p2->ship_counts)) {
    if(!playerTurn) {
      printf("Player 1's Turn\n");
      print_board(p1->guess);
      print_board(p1->board);
      make_guess(p2->board, p1->guess, p2->ship_counts);
      playerTurn = 1;
    } else {
      printf("Player 2's Turn\n");
      print_board(p2->guess);
      print_board(p2->board);
      make_guess(p1->board, p2->guess, p1->ship_counts);
      playerTurn = 0;
    }
  }
  if(!playerTurn) {
    printf("Player 2 Wins!\n");
  } else {
    printf("Player 1 Wins!\n");
  }
  return 0;
}
