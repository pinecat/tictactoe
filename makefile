all:				tictactoe

tictactoe:	tictactoe.c tictactoe.h
	gcc -lncurses -o tictactoe tictactoe.c

clean:
	rm -f *.o tictactoe
