#ifndef SNAKE_H
#define SNAKE_H

#include <time.h>

#define MAP_SIZE_X 40
#define MAP_SIZE_Y 20
#define SNAKE_START_SIZE 5

typedef enum{
	SNAKE_INIT,
	SNAKE_RUN,
	SNAKE_IDLE,
	SNAKE_GAME_OVER,
} snake_state_e;

typedef enum{
	NONE = 0,

	LEFT = -1,
	RIGHT = 1,
	
	UP = -1,
	DOWN = 1,
}direction_e;

typedef struct{
	uint16_t x;
	uint16_t y;
}point_t;

typedef struct snake_segment_t{
	point_t point;
	struct snake_segment_t* next;
	struct snake_segment_t* prev;
}snake_segment_t;

typedef struct snake_t{
	snake_segment_t* segments;
	snake_state_e state;
	
	uint16_t len;
	uint16_t max_size;
	uint16_t score;

	point_t food;
	
	direction_e direction_x;
	direction_e direction_y;

	uint16_t offset_y;
	uint16_t offset_x;
	
	clock_t time_now;	

	bool run;
}snake_t;

void snake_map_draw(uint8_t size_y, uint8_t size_x);
void snake_food_draw(void);
void snake_draw(void);
bool snake_check_food_cords(uint16_t y, uint16_t x);
void snake_generate_food(void);
void snake_connect_points(uint16_t idx);
void snake_assign_default_cords(void);
bool snake_is_move_allowed(clock_t time);
bool snake_is_key_pressed(void);
void snake_move(void);
bool snake_is_eaten(void);
bool snake_is_collision(void);
void snake_run(void);
void snake_game_over(void);
void snake_run_game(void);

#endif
