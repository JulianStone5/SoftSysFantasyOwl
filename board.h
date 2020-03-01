#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rows, cols;
void make_board(int board[rows][cols]);
void print_board(int board[rows][cols]);
void make_ship_counts(int ship_counts[5]);
int isColliding(int board[rows][cols],int s[2], int ship_size, int dir);
void build_board(int board[rows][cols]);
void make_guess(int board[rows][cols], int guess[rows][cols], int ship_counts[5]);
