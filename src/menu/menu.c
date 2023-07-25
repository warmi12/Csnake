#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ncurses.h>

#include "menu.h"

static uint16_t max_row, max_col, center_row, center_col;
static char menu_strings[MENU_SIZE][MENU_MAX_STRING_SIZE] = {"NEW GAME","HIGH SCORE","OPTIONS","EXIT", "KAROLINKA"};
static menu_state_e menu_state;


void get_screen_size(void){

	getmaxyx(stdscr,max_row,max_col);

	if(max_row < MIN_ROW_SIZE || max_col < MIN_COL_SIZE){
	
		printw("Too small screen size: %d x %d\n", max_row, max_col);
		printw("Minimum: %d x %d\n", MIN_ROW_SIZE, MIN_COL_SIZE);
		printw("Press any button to exit");
		refresh();
	        getch();
	  	endwin();
		exit(1);
	}
}

void menu_init(void){
	
	/*ncurses functions block */
	initscr();
	keypad(stdscr, TRUE);
	start_color();
	get_screen_size();	
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
}

void menu_draw(void){

	uint8_t menu_counter = 0;
	int16_t offset_row = MENU_SIZE - 1;
	
	center_row = (max_row/2);
	center_col = (max_col/2);

	while(menu_counter < MENU_SIZE){
		
		uint16_t row = (uint16_t)(center_row - offset_row);
		uint16_t col = (max_col-(uint16_t)strlen(menu_strings[menu_counter]))/2;
		mvprintw(row, col, "%s\n", menu_strings[menu_counter]);  	
		
		offset_row = offset_row - 2;
		menu_counter++;
	}

	move(max_row/2, 20);
	refresh();
//        getch();
//        endwin();

}

void menu_set_next_state(menu_state_e menu_next_state){
	menu_state = menu_next_state;
}

void menu(void){

	while(1){
		switch(menu_state){
			case INIT:
				menu_init();
				menu_set_next_state(DRAW);
				break;
			case DRAW:
				menu_draw();
				menu_set_next_state(SELECT);
				break;
			case SELECT:
				int ch = getch()
				menu_set_next_state(IDLE);
				break;
			default:
				break;
		}

		refresh();
	}

}
