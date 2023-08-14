#include <ncurses.h>

#include "screen.h"

screen_params_t screen_params;

void screen_get_size(void){

	getmaxyx(stdscr,screen_params.max_row,screen_params.max_col);

	if(screen_params.max_row < MIN_ROW_SIZE || screen_params.max_col < MIN_COL_SIZE){
	
		printw("Too small screen size: %d x %d\n", screen_params.max_row, screen_params.max_col);
		printw("Minimum: %d x %d\n", MIN_ROW_SIZE, MIN_COL_SIZE);
		printw("Press any button to exit");
		refresh();
	        getch();
	  	endwin();
		exit(1);
	}

	screen_params.center_row = (screen_params.max_row/2);
	screen_params.center_col = (screen_params.max_col/2);
}

void screen_init(void){
	
	initscr();
	keypad(stdscr, TRUE);
	start_color();
	screen_get_size();	
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	noecho();
	curs_set(0);
}
