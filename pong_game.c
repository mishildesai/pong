/*****************************************************************************
* Class: TEJ3M1 - Period 2               	 |      
* Teacher: Mr. Gunby
* Name: Mishil Desai  ( ͡° ͜ʖ ͡°)			    	     *
* Program: Pong v0.1
* Due Date: Friday, January 30th, 2015					|
*****************************************************************************/

/*****************************************************************************
* Variable Dictionary:
* maxX: stores the maximum width of the window
* maxY: stores the maximum length of the window
* xPosPlayer: the x position of the player's paddle (constant)
* yPosPlayer: the y position of the player's paddle
* directionPlayer: the change in the y position of the player's paddle
* scorePlayer: holds the score/points of the player
* xPosPlayer2: the x position the second player's paddle (constant)
* yPosPlayer2: the y position of the second player's paddle
* directionPlayer2: the change in the y position of the second player's paddle
* scorePlayer2: holds the score/points of the second player
* xPosProjectile: the x position of the ball/projectile
* yPosProjectile: the y position of the ball/projectile
* deltaX: the change in the x position of the ball/projectile
* deltaY: the change in the y position of the ball/projectile
* maxScore: the score/points needed to win the game
* playerInput: keyboard input for the first and second player
* input: used for starting and pausing the game at the user's discretion
******************************************************************************/

/******************************************************************************
* COLOR_BLACK   0
* COLOR_RED     1
* COLOR_GREEN   2
* COLOR_YELLOW  3         // Various colours for curses
* COLOR_BLUE    4
* COLOR_MAGENTA 5
* COLOR_CYAN    6
* COLOR_WHITE   7
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>

int maxX = 0, maxY = 0;
int xPosPlayer = 0, yPosPlayer = 0;
int xPosPlayer2 = 0, yPosPlayer2 = 0;
int xPosProjectile = 0, yPosProjectile = 0;
int deltaX = 1, deltaY = -1; 
int directionPlayer = 0, directionPlayer2 = 0;
int scorePlayer = 0, scorePlayer2 = 0;
int maxScore = 5;
char playerInput, input = 'n';

int main (void) {

	initscr();  /* initialize the curses library */
	start_color();
  	cbreak();   /* take input chars one at a time*/
  	timeout(1);
  	curs_set(0); /* Don't show blinking cursor */
  	noecho();	/* don't echo input */
	resize_term(24, 80); /* Resize the terminal/cmd window */
	
	getmaxyx(stdscr, maxY, maxX);

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);

	// Variable initialization
	xPosPlayer = 2;
	xPosPlayer2 = maxX - 3;
	yPosPlayer2 = maxY - 1;
	xPosProjectile = maxX / 2;
	yPosProjectile = maxY / 2;

	while (1) {

		// Break Point
		if (scorePlayer + scorePlayer2 >= 8 && (scorePlayer2 == scorePlayer)) {
			
			attron (A_BOLD);
			attron (COLOR_PAIR(1));
			mvprintw(maxY / 2 - 1, maxX / 2 - 6, "Break Point!");
			attroff (COLOR_PAIR(1));
			attroff (A_BOLD);

		}
		
		// Exits loop when a player wins
		if (scorePlayer == maxScore) {
			
			sleep(2);
			attron (A_BOLD);
			attron (COLOR_PAIR(2));
			mvprintw (maxY / 2, maxX / 2 - 4, "LEFT WON!");
			refresh();
			sleep(3);
			break;

		} else if (scorePlayer2 == maxScore) {
	
			sleep(2);
			attron (A_BOLD);
			attron (COLOR_PAIR(2));
			mvprintw (maxY / 2, maxX / 2 - 5, "RIGHT WON!");
			refresh();
			sleep(3);
			break;

		}

		// Stops paddles from moving once no key is pressed
		directionPlayer = 0;
		directionPlayer2 = 0;

		attron (A_BOLD);
		attron (COLOR_PAIR(3));

		// Prints Player 1's paddle		
		mvaddstr(yPosPlayer, xPosPlayer, "|");    
 	        mvaddstr(yPosPlayer + 1, xPosPlayer, "|");
   	        mvaddstr(yPosPlayer + 2, xPosPlayer, "|");
                mvaddstr(yPosPlayer + 3, xPosPlayer, "|");

		// Prints Player 2's paddle
		mvaddstr(yPosPlayer2, xPosPlayer2, "|");
		mvaddstr(yPosPlayer2 - 1, xPosPlayer2, "|");
		mvaddstr(yPosPlayer2 - 2, xPosPlayer2, "|");
		mvaddstr(yPosPlayer2 - 3, xPosPlayer2, "|"); 
		attroff (COLOR_PAIR(3));

		// Prints the projectile
		attron (COLOR_PAIR(2));
		mvaddstr(yPosProjectile, xPosProjectile, "o");
		attroff (COLOR_PAIR(2));

		// Prints the score to the window
		attron (COLOR_PAIR(2));
		mvprintw(maxY / 2, maxX / 2 - 3, "%d", scorePlayer);
		mvprintw(maxY / 2, maxX / 2 + 2, "%d", scorePlayer2);
		attroff (COLOR_PAIR(2));
		mvprintw(maxY / 2, maxX / 2 - 1, "||");

		attron (COLOR_PAIR(5));
		mvprintw(maxY / 2 + 1, maxX / 2 - 3, "Win: %d", maxScore);
		attroff (COLOR_PAIR(5));

		attroff (A_BOLD);

		// Prints the title
		attron(A_STANDOUT);
		attron (A_BOLD);
		attron (COLOR_PAIR(2));
		mvprintw(0, maxX / 2 - 5, "PONG v0.2");
		attroff (COLOR_PAIR(2));
		attroff (A_BOLD);
		attroff(A_STANDOUT);

		attron (A_BOLD);
		mvprintw(maxY - 1, maxX / 2 - 8, "© 2015 Mishil D.");

		// Displays when game is paused
		attron (COLOR_PAIR(4));
		if (input != 's') {

			mvprintw (maxY - 2, maxX / 2 - 9, "Press [S] to start"); 

		// Displays when game is not paused
		} else {

			mvprintw(maxY - 2, maxX / 2 - 9, "Press [P] to pause");		
	
		}
		attron (COLOR_PAIR(4));

		attroff (A_BOLD);
	
		refresh();
    		usleep (65000);

		// Pauses the game
		while (input != 's') {
			
			input = getch();
	
		}
		
		// Gets input from keyboard to control paddles
		playerInput = getch();

		// Player 1's controls
		switch (playerInput) {

			case 'w' :

				if (yPosPlayer == 0) {

					directionPlayer = 0;

				} else {

					directionPlayer = -2;

				}

				break;

			case 's' :

				if ((yPosPlayer + 4) >= maxY) {

					directionPlayer = 0;

				} else {

					directionPlayer = 2;

				}
			
				break;

		// Player 2's controls
			case 'o' :

				if ((yPosPlayer2  - 3) == 0) {

					directionPlayer2 = 0;

				} else {

					directionPlayer2 = -2;

				}

				break;

			case 'l' :

				if ((yPosPlayer2 + 1) >= maxY) {

					directionPlayer2 = 0;

				} else {

					directionPlayer2 = 2;

				}

				break;

		// Pauses the game 
			case 'p' :

				input = 'n';

		}
	
		// Clears previous "images" of the object
		clear();	

		// Checks for edge collision on the y plane
		if (yPosProjectile <= 0) {

			printw ("\0x07");
			deltaY = 1;

		} else if ((yPosProjectile + 1) == maxY) {

			printw ("\0x07");
			deltaY = -1;

		} 

		// Checks for edge collision or the x plane and adds to score accordingly
		if (xPosProjectile == 0) {

			deltaX = 1;
			scorePlayer2 += 1;

			yPosProjectile = maxY / 2;
			xPosProjectile = maxX / 2;

			usleep(500000);		

			// Break Point
			if (scorePlayer + scorePlayer2 >= 8 && (scorePlayer2 == scorePlayer)) {

				maxScore += 1; 

			}

		} else if ((xPosProjectile + 2) == maxX) {

			deltaX = -1;
			scorePlayer += 1;

			yPosProjectile = maxY / 2;
			xPosProjectile = maxX / 2;	

			usleep(500000);					

			// Break Point;
			if (scorePlayer + scorePlayer2 >= 8 && (scorePlayer2 == scorePlayer)) {

				maxScore += 1; 

			}

		}

		// Checks for collision on Player 1's paddle and bounces accordingly
		if ((xPosProjectile == xPosPlayer) && (yPosProjectile ==  yPosPlayer) && (deltaX == -1)) {

			deltaX = 1;

		} else if ((xPosProjectile == xPosPlayer) && (yPosProjectile == yPosPlayer + 1) && (deltaX == -1)) {

			deltaX = 1;
		
		} else if ((xPosProjectile == xPosPlayer) && (yPosProjectile == yPosPlayer + 2) && (deltaX == -1)) {

			deltaX = 1;

		} else if ((xPosProjectile == xPosPlayer) && (yPosProjectile == yPosPlayer + 3) && (deltaX == -1)) {

			deltaX = 1;

		} 

		// Checks for collision on Player 2's paddle and bounces accordingly
		if ((xPosProjectile == xPosPlayer2) && (yPosProjectile == yPosPlayer2) && (deltaX == 1)) {

			deltaX  = -1;

		} else if ((xPosProjectile == xPosPlayer2) && (yPosProjectile == yPosPlayer2 - 1) && (deltaX == 1)) {

			deltaX = -1;

		} else if ((xPosProjectile == xPosPlayer2) && (yPosProjectile == yPosPlayer2 - 2) && (deltaX == 1)) { 

			deltaX = -1;

		} else if ((xPosProjectile == xPosPlayer2) && (yPosProjectile == yPosPlayer2 - 3) && (deltaX == 1)) {

			deltaX = -1;

		}

		// Changes the x and y positions of the "objects"
		yPosPlayer += directionPlayer;
		yPosPlayer2 += directionPlayer2;
		xPosProjectile += deltaX;
		yPosProjectile += deltaY;


	}	

	endwin();
	return 0;

}
