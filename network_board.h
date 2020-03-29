#include "board.h"

int wait_time;
int getDir_server(char * input, int new_socket);
void getInfo(int sock);
void getStart_server(int board[rows][cols],char * input, int s[2],int ship_size, int dir, int new_socket);
void build_board_server(int board[rows][cols], int new_socket);
void build_board_client(int sock);
void make_guess_server(int board[rows][cols], int guess[rows][cols], int ship_counts[5], int new_socket);
void make_guess_client(int sock);
