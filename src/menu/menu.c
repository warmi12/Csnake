#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ncurses.h>
#include <stdbool.h>

#include "screen.h"
#include "menu.h"
#include "snake.h"

uint16_t selected_row, top_row, end_row;
static char menu_strings[MENU_SIZE][MENU_MAX_STRING_SIZE] = {"NEW GAME","HIGH SCORE","OPTIONS","EXIT"};
static menu_state_e menu_state;

extern screen_params_t screen_params;

void menu_draw(void){

	uint8_t menu_counter = 0;
	int16_t offset_row = MENU_SIZE - 1;
	
	top_row = screen_params.center_row - (MENU_SIZE - 1);
	end_row = screen_params.center_row + (MENU_SIZE - 1);

	while(menu_counter < MENU_SIZE){
		
		uint16_t row = (uint16_t)(screen_params.center_row - offset_row);
		uint16_t col = (screen_params.max_col-(uint16_t)strlen(menu_strings[menu_counter]))/2;
		mvprintw(row, col, "%s\n", menu_strings[menu_counter]);  	
		
		offset_row = offset_row - 2;
		menu_counter++;
	}


	selected_row = top_row;
	menu_highlight_row(selected_row);
	refresh();
}

void menu_set_next_state(menu_state_e menu_next_state){
	menu_state = menu_next_state;
}

void menu_highlight_row(uint16_t row){
	mvchgat(row, 0, -1, A_BLINK | A_BOLD, 1, NULL);
}

void menu_unhighlight_row(uint16_t row){
	mvchgat(row, 0, -1, A_NORMAL, 0, NULL);
}

void menu_button_process(int button){
	
	if(button == KEY_UP){
		
		menu_unhighlight_row(selected_row);

		if(selected_row == top_row){
			selected_row = end_row;
		}		
		else{
			selected_row = selected_row - 2;
		}

		menu_highlight_row(selected_row);
	}
	else if(button == KEY_DOWN){
		
		menu_unhighlight_row(selected_row);

		if(selected_row == end_row){
			selected_row = top_row;
		}
		else{
			selected_row = selected_row + 2;
		}

		menu_highlight_row(selected_row);
	}
	else if(button == KEY_MY_ENTER){
		menu_state_e menu_next_state = ((selected_row - top_row) / 2) + 2;
		menu_set_next_state(menu_next_state);
	}

}

void menu(void){

	bool loop = 1;
	int button = 0;

	while(loop){
		switch(menu_state){
			case MENU_DRAW:
				menu_draw();
				menu_set_next_state(MENU_SELECT);
				break;
			case MENU_SELECT:
				button = getch();
				menu_button_process(button);
				break;
			case MENU_START_GAME:
				clear();
				refresh();
				snake_run_game();//parameters for lvl itd? screen size?
				break;				
			default:
				break;
		}

		//refresh();
	}

}
