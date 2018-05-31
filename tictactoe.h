#ifndef TICTACTOE_H
#define TICTACTOE_H

/* imports */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>

/* constants */
#define Y_CENTER 2
#define X_CENTER 12

/* prototypes */
void init_curses();
void startgame();
void print_board(char gameboard[5][100]);
void turn(int player, char gameboard[5][100]);
int valid(int y, int x, char gameboard[5][100]);
int check(int player, char gameboard[5][100]);
int check_row(char ch1, char ch2, char ch3);
void wrap_up();

#endif
