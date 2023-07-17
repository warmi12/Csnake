#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "menu.h"

int max_row, max_col;
char str[10] = "maciek";
//get center of screen?i

void get_screen_size(void){

	getmaxyx(stdscr,max_row,max_col);

	if(max_row < MIN_ROW_SIZE || max_col < MIN_COL_SIZE){
		exit(1);
	}
}

void init(void){

	initscr();
	get_screen_size();	
	mvprintw(max_row/2,(max_col-strlen(str))/2,"%s","maciek"); 

	move(max_row/2, (max_col-strlen(str))/2-1);
	
	
	refresh();
        getch();
        endwin();
}


void menu(void){

	init();


}
