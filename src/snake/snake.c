#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "screen.h"
#include "snake.h"

//TODO READ FROM CONF
//#define MAP_SIZE_X 40
//#define MAP_SIZE_Y 20
//#define SNAKE_START_SIZE 5

//snake_state_e snake_state; //


//snake_t* snake; //
//u/int16_t snake_len;
//uint16_t snake_max_size;
//point_t food;
//int8_t direction_x;
//int8_t direction_y;
//uint16_t offset_y;
//uint16_t offset_x;
//bool run = 1;

//clock_t time_now, end;
extern screen_params_t screen_params;
snake_t snake; 

void snake_map_draw(uint8_t size_y, uint8_t size_x){
	
	snake.offset_y = screen_params.center_row - size_y/2;
	snake.offset_x = screen_params.center_col - size_x/2;

	for(uint16_t y = snake.offset_y; y <= size_y + snake.offset_y; y++){

		for(uint16_t x = snake.offset_x; x <= size_x + snake.offset_x; x++){
			
			mvprintw(y,x,"#");

			if(y != snake.offset_y && y != snake.offset_y + size_y){
				x=snake.offset_x + size_x;
				mvprintw(y,x,"#");
			}
		}
	}

	refresh();
}

void snake_food_draw(void){
	
	mvprintw(snake.food.y, snake.food.x, "O");
}

void snake_draw(void){

	uint16_t idx = 0;
	
	do{
		mvprintw(snake.segments[idx].point.y, snake.segments[idx].point.x, "X");
		idx++;
	}
	while(snake.segments[idx].prev != NULL);
}

void snake_generate_food(void){
	
	snake.food.y = rand() % (MAP_SIZE_Y - 2);		
	snake.food.x = rand() % (MAP_SIZE_X - 2);
	
	snake.food.y = snake.food.y + (snake.offset_y + 2);
	snake.food.x = snake.food.x + (snake.offset_x + 2);
}

void snake_connect_points(uint16_t idx){
	
	snake.segments[idx].prev = &snake.segments[idx - 1];
	snake.segments[idx - 1].next = &snake.segments[idx];
}

void snake_assign_default_cords(void){
	
	for(uint16_t idx = 0; idx < snake.len; idx++){
		snake.segments[idx].point.x = screen_params.center_col + idx;
		snake.segments[idx].point.y = screen_params.center_row;
	       	
		if(idx > 0){
			snake_connect_points(idx);	
		}
	}
}

bool snake_is_move_allowed(clock_t past_time){

	clock_t present_time = clock();
	
	double time_up = ((double) (present_time - past_time)) / CLOCKS_PER_SEC;

	if ( time_up > 0.1 ){
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

void snake_move(void){

	for(uint16_t idx = snake.len - 1; idx >= 1; idx--){
					
		snake.segments[idx].point.x = snake.segments[idx-1].point.x;	
		snake.segments[idx].point.y = snake.segments[idx-1].point.y;
	}

	snake.segments[0].point.x += snake.direction_x;
	snake.segments[0].point.y += snake.direction_y;
}

bool snake_is_eaten(void){

	if(snake.segments[0].point.x == snake.food.x && snake.segments[0].point.y == snake.food.y){
		return 1;
	}
	else{
		return 0;
	}
}

bool snake_is_collision(void){

	if(snake.segments[0].point.y == snake.offset_y || snake.segments[0].point.y == snake.offset_y + MAP_SIZE_Y){
			
		return 1;
	}
	else if(snake.segments[0].point.x == snake.offset_x || snake.segments[0].point.x == snake.offset_x + MAP_SIZE_X){
		
		return 1;
	}
	else{
		
		for(uint16_t idx = 1; idx < snake.len; idx++){
					
			if(snake.segments[0].point.x == snake.segments[idx].point.x && snake.segments[0].point.y == snake.segments[idx].point.y){

				return 1;
			}

		}
	}
	
	return 0;
}

void snake_run(void){
	
	snake.time_now = clock();

	while(snake.run){

		if(snake_is_move_allowed(snake.time_now)){
			
			snake.time_now = clock();
		
			if(snake_is_key_pressed()){
				int ch = getch();
				switch(ch){
					case KEY_UP:
						if(snake.direction_y != DOWN){
							snake.direction_y = UP;
							snake.direction_x = NONE;
						}
						break;
					case KEY_DOWN:
						if(snake.direction_y != UP){
							snake.direction_y = DOWN;
							snake.direction_x = NONE;
						}
						break;
					case KEY_LEFT:
						if(snake.direction_x != RIGHT){
							snake.direction_y = NONE;
							snake.direction_x = LEFT;
						}
						break;
					case KEY_RIGHT:
						if(snake.direction_x != LEFT){
							snake.direction_y = NONE;
							snake.direction_x = RIGHT;
						}
						break;
					default:
						break;
				}
				
			}

			if(snake_is_eaten()){
			
				snake.segments[snake.len].point.x = snake.segments[snake.len - 1].point.x;
				snake.segments[snake.len].point.y = snake.segments[snake.len - 1].point.y;
			
				snake_connect_points(snake.len);
				
				snake.len++;

				snake_generate_food();
			}

			snake_move();

			if(snake_is_collision()){
				snake.run = 0;
			}		
			else{
				clear();

				snake_map_draw(MAP_SIZE_Y + 2, MAP_SIZE_X + 2);
				snake_map_draw(MAP_SIZE_Y,MAP_SIZE_X);
				
				snake_draw();
				snake_food_draw();	
				
				refresh();
			}
		}
	}
	
}

void snake_game_over(){
;
}

void snake_init(void){
	
	snake_map_draw(MAP_SIZE_Y + 2, MAP_SIZE_X + 2);
	snake_map_draw(MAP_SIZE_Y,MAP_SIZE_X);

	snake.len = SNAKE_START_SIZE;

	snake.max_size = (MAP_SIZE_Y - 2) * (MAP_SIZE_X - 2);
	snake.segments = (snake_segment_t*)malloc(sizeof(snake_segment_t) * snake.max_size);

	srand(time(NULL));
	snake_generate_food();
       
	snake_assign_default_cords();

	snake_food_draw();
	snake_draw();
	
	snake.direction_x = LEFT;
	snake.direction_y = NONE;
	
	snake.run = 1;
}

void snake_run_game(void){

	while(1){
		switch(snake.state){
			case SNAKE_INIT:
				snake_init();
				snake.state = SNAKE_RUN;
				break;
			case SNAKE_RUN:
				snake_run();
				snake.state = SNAKE_GAME_OVER;
				break;
			case SNAKE_GAME_OVER:
				snake_game_over();
				break;
			default:
				break;
		}
	}
}
