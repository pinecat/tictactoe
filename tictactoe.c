/**********************************************
*
*   Project Name:   tictactoe
*   Description:      simple tictactoe in ncurses
*   Filenames:        tictactoe.c tictactoe.h
*   Author:             rory
*
*********************************************/

/* imports */
#include "tictactoe.h"

int main()
{
    init_curses();
    printw("_|_  .   _  _|_   _    _  _|_   _    _   \n");
    printw(" |   |  (_   |   (_|  (_   |   (_)  (/_   \n");
    printw("\nPress ENTER to continue....");
    getch();
    clear();
    startgame();
    getch();
    wrap_up();
    return 0;
}

void init_curses()
{
    initscr(); // creates stdscr
    cbreak(); // allows exiting of the program with C-z or C-c
    keypad(stdscr, 1);
    noecho(); // turn off character echoing
}

void startgame()
{
    char gameboard[5][100];
    sprintf(gameboard[0], "+-----------------------+");
    sprintf(gameboard[1], "|       |       |       |");
    sprintf(gameboard[2], "|       |       |       |");
    sprintf(gameboard[3], "|       |       |       |");
    sprintf(gameboard[4], "+-----------------------+");
    print_board(gameboard);

    int player1 = 1; // player X (they will always go first)
    int player2 = 2; // player O (they will always go second)

    int gvalue = 0;
    while (1) {
        turn(player1, gameboard);
        if ((gvalue = check(player1, gameboard)) != 0) break;
        turn(player2, gameboard);
        if ((gvalue = check(player2, gameboard)) != 0) break;
    }

    switch (gvalue) {
        case 1: {
            printw("\nPlayer X wins!");
        } break;

        case 2: {
            printw("\nPlayer O wins!");
        } break;

        case 3: {
            printw("\nDraw!");
        } break;
    }

    printw("\n\nPress ENTER to continue....");
}

void print_board(char gameboard[5][100])
{
    clear();
    int i;
    for (i = 0; i < 5; i++) {
        printw("%s\n", gameboard[i]);
    }
    refresh();
}

void turn(int player, char gameboard[5][100])
{
    int break_char_up;
    int break_char_lo;
    if (player == 1) {
        printw("\nPlayer X's turn....");
        break_char_up = 'X';
        break_char_lo = 'x';
    } else {
        printw("\nPlayer O's turn....");
        break_char_up = 'O';
        break_char_lo = 'o';
    }
    int y = Y_CENTER; // ycoord of middle of gameboard
    int x = X_CENTER; // xcoord of middle of gameboard
    move(y, x); // move cursor to center of gameboard
    refresh(); // refresh the screen, so the cursor updates location
    while (1) {
        int ch = getch();
        int blank = 1;

        if (ch == KEY_LEFT) {
            x--;
        } else if (ch == KEY_RIGHT) {
            x++;
        } else if (ch == KEY_UP) {
            y--;
        } else if (ch == KEY_DOWN) {
            y++;
        } else if ((ch == 'X' || ch == 'x') && player == 1) {
            if (x >= 1 && x <= 7) {
                blank = valid(y, 1, gameboard);
            } else if (x >= 9 && x <= 15) {
                blank = valid(y, 9, gameboard);
            } else if (x >= 17 && x <= 23) {
                blank = valid(y, 17, gameboard);
            } else {
                print_board(gameboard);
                printw("\nInvalid location!  Still player X's turn....");
                y = Y_CENTER;
                x = X_CENTER;
            }

            if (blank != 0) {
                mvwaddch(stdscr, y, x, toupper(ch));
                gameboard[y][blank] = toupper(ch);
            } else {
                print_board(gameboard);
                printw("\nInvalid location!  Still player X's turn....");
                y = Y_CENTER;
                x = X_CENTER;
            }
        } else if ((ch == 'O' || ch == 'o') && player == 2) {
            if (x >= 1 && x <= 7) {
                blank = valid(y, 1, gameboard);
            } else if (x >= 9 && x <= 15) {
                blank = valid(y, 9, gameboard);
            } else if (x >= 17 && x <= 23) {
                blank = valid(y, 17, gameboard);
            } else {
                print_board(gameboard);
                printw("\nInvalid location!  Still player O's turn....");
                y = Y_CENTER;
                x = X_CENTER;
            }

            if (blank != 0) {
                mvwaddch(stdscr, y, x, toupper(ch));
                gameboard[y][blank] = toupper(ch);
            } else {
                print_board(gameboard);
                printw("\nInvalid location!  Still player O's turn....");
                y = Y_CENTER;
                x = X_CENTER;
            }
        } else {
            print_board(gameboard);
            printw("\nInvalid character or location!");
            if (player == 1) {
                printw("  Still player X's turn....");
            } else {
                printw("  Still player O's turn...");
            }
        }
        move(y, x);
        refresh();
        if ((ch == break_char_up || ch == break_char_lo) && blank != 0) break;
    }
    print_board(gameboard);
}

int valid(int y, int x, char gameboard[5][100])
{
    int i;
    for (i = x; i <= x+6; i++) {
        if (gameboard[y][i] != ' ') return 0;
    }
    if (x == 1) return 4;
    if (x == 9) return 12;
    if (x == 17) return 20;
}

int check(int player, char gameboard[5][100])
{
    int i, j; // indexes
    int win = 0; // hold win value (0 - no winner yet, 1 - player x wins, 2 - player o wins, 3 - tie)

    // check rows
    for (i = 1; i <= 3; i++) {
        if (win = check_row(gameboard[i][4], gameboard[i][12], gameboard[i][20])) {
            return win;
        }
    }

    // check cols
    for (i = 4; i <= 20; i += 8) {
        if (win = check_row(gameboard[1][i], gameboard[2][i], gameboard[3][i])) {
            return win;
        }
    }

    // check diags
    if (win = check_row(gameboard[1][4], gameboard[2][12], gameboard[3][20])) {
        return win;
    }

    if (win = check_row(gameboard[3][4], gameboard[2][12], gameboard[1][20])) {
        return win;
    }

    // check for tie (really, check for remaining moves)
    if (win == 0) {
        for (i = 1; i <= 3; i++) {
            for (j = 4; j <= 20; j += 8) {
                if (gameboard[i][j] == ' ') { // a move still exists
                    return win;
                }
            }
        }
    }

    return (win = 3);
}

int check_row(char ch1, char ch2, char ch3)
{
    if ((ch1 == ch2) && (ch1 == ch3)) {
        if (ch1 == 'X') {
            return 1;
        } else if (ch1 == 'O') {
            return 2;
        }
    }
    return 0;
}

void wrap_up()
{
    curs_set(1); // reset cursor pos
    clear(); // clear the display
    endwin(); // close (free memory of) stdscr and ends curses session
}
