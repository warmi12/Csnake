#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "screen.h"
#include "snake.h"

extern screen_params_t screen_params;
uint16_t best_score = 5;
uint8_t counter = 0;
snake_t snake; 

void snake_map_draw(uint8_t size_y, uint8_t size_x){
	
	snake.offset_y = screen_params.center_row - size_y/2;
	snake.offset_x = screen_params.center_col - size_x/2;

	for(uint16_t y = snake.offset_y; y <= size_y + snake.offset_y; y++){

		for(uint16_t x = snake.offset_x; x <= size_x + snake.offset_x; x++){
			
			mvprintw(y,x,"#");
			mvchgat(y, x, 1, A_NORMAL, 2, NULL);

			if(y != snake.offset_y && y != snake.offset_y + size_y){
				x=snake.offset_x + size_x;
				mvprintw(y,x,"#");
				mvchgat(y, x, 1, A_NORMAL, 2, NULL);
			}
			
		}
	}

	refresh();
}

void snake_food_draw(void){
	
	mvprintw(snake.food.y, snake.food.x, "O");
	mvchgat(snake.food.y, snake.food.x, 1, A_NORMAL, 1, NULL);
}

void snake_draw(void){

	uint16_t idx = 0;
	
	do{
		mvprintw(snake.segments[idx].point.y, snake.segments[idx].point.x, "X");
		mvchgat(snake.segments[idx].point.y, snake.segments[idx].point.x, 1, A_NORMAL, 3, NULL);
		idx++;
	}
	while(snake.segments[idx].prev != NULL);
	
	mvchgat(snake.segments[0].point.y, snake.segments[0].point.x, 1, A_NORMAL | A_BOLD, 3, NULL);
}

bool snake_check_food_cords(uint16_t y, uint16_t x){

	for(uint16_t idx = 0; idx < snake.len; idx++){
	
		if(snake.segments[idx].point.y == y && snake.segments[idx].point.x == x){

			return 1;
		}
	}
	
	return 0;
}

void snake_generate_food(void){
	
	bool run = 1;
	
	while(run){
	
		snake.food.y = rand() % (MAP_SIZE_Y - 2) + (snake.offset_y + 2);		
		snake.food.x = rand() % (MAP_SIZE_X - 2) + (snake.offset_x + 2);
		
		run = snake_check_food_cords(snake.food.y, snake.food.x);
	}	
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
				snake.score++;
				
				if(snake.score > best_score){
					best_score = snake.score;
				}

				snake_generate_food();
			}

			snake_move();

			if(snake_is_collision()){
				snake.run = 0;
			}		
			else{
				clear();
				
				mvprintw(0,0,"%d",counter);
				snake_map_draw(MAP_SIZE_Y + 2, MAP_SIZE_X + 2);
				snake_map_draw(MAP_SIZE_Y,MAP_SIZE_X);
				
				mvprintw(screen_params.center_row - (MAP_SIZE_Y + 6)/2, \
					screen_params.center_col - MAP_SIZE_X / 2, "SCORE: %d", snake.score);

				mvprintw(screen_params.center_row - (MAP_SIZE_Y + 6)/2, \
					screen_params.center_col + (MAP_SIZE_X / 4) - 2, "BEST SCORE: %d", best_score);
				
				snake_food_draw();
				snake_draw();
			
				refresh();
			}
		}
	}
	
}

void snake_game_over(void){
	
	const char* game_over = "GAME OVER!";
	uint8_t len = strlen(game_over);
	
	nodelay(stdscr, FALSE);
	
	mvprintw(screen_params.center_row, screen_params.center_col - len / 2, "%s", game_over);
	refresh();
	sleep(1);
}

void snake_init(void){
	
	nodelay(stdscr, TRUE);
	
	snake_map_draw(MAP_SIZE_Y + 2, MAP_SIZE_X + 2);
	snake_map_draw(MAP_SIZE_Y,MAP_SIZE_X);
 
	snake.len = SNAKE_START_SIZE;
	snake.score = SNAKE_START_SIZE;
	//best_score = SNAKE_START_SIZE;

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

void snake_deinit(void){
	
	memset(snake.segments, 0, sizeof(snake_segment_t)*snake.len);
	free(snake.segments);
	memset(&snake, 0, sizeof(snake_t));
}

void snake_run_game(void){
	
	bool run = 1;
	
	while(run){
		switch(snake.state){
			case SNAKE_INIT:
				snake_init();
				snake.state = SNAKE_RUN;
				break;
			case SNAKE_RUN:
				snake_run();
				snake_deinit();
				snake.state = SNAKE_GAME_OVER;
				break;
			case SNAKE_GAME_OVER:
				snake_game_over();
				getch();
				run = 0;
				snake.state = SNAKE_INIT;
				break;
			default:
				break;
		}
	}
}
