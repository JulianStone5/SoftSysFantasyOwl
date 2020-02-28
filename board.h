#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_board(int *board, int rows, int cols);
void print_board(int *board, int rows, int cols);
int isColliding(int * board, int * s, int ship_size, int dir, int cols);
void build_board(int *board, int rows, int cols);
