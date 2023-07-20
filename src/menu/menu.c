#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ncurses.h>

#include "menu.h"

int max_row, max_col;
char menu_strings[MENU_SIZE][MENU_MAX_STRING_SIZE] = {"NEW GAME","HIGH SCORE","OPTIONS","EXIT", "KAROLINKA"};
//get center of screen?i

void get_screen_size(void){

	getmaxyx(stdscr,max_row,max_col);

	if(max_row < MIN_ROW_SIZE || max_col < MIN_COL_SIZE){
		exit(1);
	}
}

void init(void){

	initscr();
	start_color();
	get_screen_size();	
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
//	mvprintw(max_row/2,(max_col-strlen(menu_strings[0]))/2,"%s",menu_strings[0]); 
	
//	mvchgat(max_row/2,(max_col-strlen(menu_strings[0]))/2-1,-1, A_BLINK | A_BOLD, 1, NULL);  
//	move(max_row-1, max_col-1);


//	refresh();
 //       getch();
  //      endwin();
}

void menu_draw(void){

	uint8_t menu_counter = 0;
	uint8_t center = (max_row/2);
	int8_t offset_row = MENU_SIZE - 1;

	while(menu_counter < MENU_SIZE){
		//uint8_t row = (max_row/2) + (menu_counter * MENU_ROW_SPACE) + menu_counter;
		uint8_t row = (uint8_t)(center - offset_row);
		uint8_t col = (max_col-strlen(menu_strings[menu_counter]))/2;
		mvprintw(row, col, "%s\n", menu_strings[menu_counter]);  	
		
		offset_row = offset_row - 2;
		menu_counter++;
	}

	move(max_row/2, 20);
	refresh();
        getch();
        endwin();

}

void menu(void){

	init(); //rozdzielic na menu_init? co jak bedziemy chcieli tylko wyswietlic menu?
	menu_draw();

}
