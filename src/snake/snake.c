#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "screen.h"
#include "snake.h"

//TODO READ FROM CONF
#define MAP_SIZE_X 60
#define MAP_SIZE_Y 30
#define SNAKE_START_SIZE 5

snake_state_e snake_state;
extern screen_params_t screen_params;

snake_t* snake;
uint16_t snake_len;
uint16_t snake_max_size;
point_t food;
int8_t direction_x;
int8_t direction_y;

clock_t start, end;

void snake_map_draw(uint8_t size_y, uint8_t size_x){
	
	uint16_t offset_y = screen_params.center_row - size_y/2;
	uint16_t offset_x = screen_params.center_col - size_x/2;

	for(uint16_t y = offset_y; y < size_y + offset_y; y++){

		for(uint16_t x = offset_x; x < size_x + offset_x; x++){
			
			mvprintw(y,x,"#");

			if(y != offset_y && y != offset_y + size_y - 1){
				x=offset_x + size_x - 1;
				mvprintw(y,x,"#");
			}
		}
	}

	refresh();
}

void snake_food_draw(void){
	//TODO zastanowic sie jak te zmienne offsetowe zrobic globalne	
	uint16_t offset_y = screen_params.center_row - ((MAP_SIZE_Y - 4) / 2);
	uint16_t offset_x = screen_params.center_col - ((MAP_SIZE_X - 4) / 2);

	mvprintw(offset_y + food.y, offset_x + food.x, "O");
}

void snake_draw(void){

	uint16_t idx = 0;
	
	do{
		mvprintw(snake[idx].point.y, snake[idx].point.x, "X");
		idx++;
	}
	while(snake[idx].prev != NULL);

	refresh();
}

void snake_init(void){
	
	snake_map_draw(MAP_SIZE_Y,MAP_SIZE_X);
	snake_map_draw(MAP_SIZE_Y - 2, MAP_SIZE_X - 2);

	snake_len = SNAKE_START_SIZE;

	snake_max_size = (MAP_SIZE_Y - 4) * (MAP_SIZE_X - 4);
	snake = (snake_t*)malloc(sizeof(snake_t) * snake_max_size);

	srand(time(NULL));
	food.y = rand() % (MAP_SIZE_Y - 4);		
	food.x = rand() % (MAP_SIZE_X - 4);
       
	for(uint16_t idx = 0; idx < snake_len; idx++){
		snake[idx].point.x = screen_params.center_col + idx;
		snake[idx].point.y = screen_params.center_row;
	       	
		if(idx > 0){
			snake[idx].prev = &snake[idx - 1];
			snake[idx - 1].next = &snake[idx];	
		}
	}

	snake_food_draw();
	snake_draw();
	direction_x = -2;
	direction_y = 0;
}

bool snake_is_move_allowed(clock_t time){

	clock_t actual_time = clock();
	
	double cpu_time_used = ((double) (actual_time - time)) / CLOCKS_PER_SEC;

	if (cpu_time_used > 1 ){
		return 1;	
	}
	else{
		return 0;
	}
}

bool snake_is_key_pressed(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void snake_run(void){
	
	start = clock();


while(1){

	if(snake_is_move_allowed(start)){
		
		start = clock();
		
		for(uint16_t idx = snake_len - 1; idx >= 1; idx--){
				
		//	if(snake[idx-1].point.x == snake[idx].point.x){
		//		snake[idx].point.x = snake[idx-1].point.x + (direction_x/2) ; 		
		//	}
		//	else{
				snake[idx].point.x = snake[idx-1].point.x;	
		//	}

			
			snake[idx].point.y = snake[idx-1].point.y;
		}

		snake[0].point.x += direction_x;
		snake[0].point.y += direction_y;

		clear();

		snake_map_draw(MAP_SIZE_Y,MAP_SIZE_X);
		snake_map_draw(MAP_SIZE_Y - 2, MAP_SIZE_X - 2);

		snake_draw();
		snake_food_draw();	
	}	

	if(snake_is_key_pressed()){
		int ch = getch();
		switch(ch){
			case KEY_UP:
				if(direction_y != 1){
					direction_y = -1;
					direction_x = 0;
				}
				break;
			case KEY_DOWN:
				if(direction_y != -1){
					direction_y = 1;
					direction_x = 0;
				}
				break;
			case KEY_LEFT:
				if(direction_x != 2){
					direction_y = 0;
					direction_x = -2;
				}
				break;
			case KEY_RIGHT:
				if(direction_x != -2){
					direction_y = 0;
					direction_x = 2;
				}
				break;
			default:
				break;
		}
		
		refresh();
	}
	else{
		refresh();
//		mvprintw(0,0,"Not Pressed");
//		refresh();
	}		
//	sleep(1);

	

}
	
}

void snake_run_game(void){

	while(1){
		switch(snake_state){
			case SNAKE_INIT:
				snake_init();
				snake_state = SNAKE_RUN;
				break;
			case SNAKE_RUN:
				snake_run();
				snake_state = SNAKE_IDLE;
				break;
			default:
				break;
		}
	}
}
