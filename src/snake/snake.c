#include <ncurses.h>

#include "screen.h"
#include "snake.h"

snake_state_e snake_state;
extern screen_params_t screen_params;

void snake_draw_map(uint8_t size_x, uint8_t size_y){
	//robic skalowanie? chyba ciezkie to berdzie 
	//map size from options?
	//przechodzenie przez sciany :)

	//for(uint16_t k = 0; k< 3; k++){
	//
	
	uint16_t offset_x = screen_params.center_col - size_x/2;
	uint16_t offset_y = screen_params.center_row - size_y/2;
//
	for(uint16_t y = offset_y; y < size_y + offset_y; y++){
		

		for(uint16_t x = offset_x; x < size_x + offset_x; x++){
			
			mvprintw(y,x,"#");
			//if(y%2==0 && x%2==0){
			//	mvchgat(y, x, 1, A_BLINK, 1, NULL);	

			//}

			if(y != offset_y && y != offset_y + size_y - 1){
				x=offset_x + size_x-1;
				mvprintw(y,x,"#");

			//if(y%2==0 && x%2==0){
		//		mvchgat(y, x, 1, A_BLINK, 1, NULL);	
		//	}
		//	}
		}
	}

	}

	refresh();
}

void snake_init(){

	
	snake_draw_map(60,30);
	snake_draw_map(58,28);
}

void snake_run_game(void){

	while(1){
		switch(snake_state){
			case SNAKE_INIT:
				snake_init();
				break;
			case SNAKE_DRAW:
				break;
			default:
				break;
		}
	}
}
