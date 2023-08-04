#ifndef SNAKE_H
#define SNAKE_H

typedef enum{
	SNAKE_INIT,
	SNAKE_RUN,
	SNAKE_IDLE
} snake_state_e;

typedef struct{
	uint16_t x;
	uint16_t y;
}point_t;

typedef struct snake_t{
	point_t point;
	struct snake_t* next;
	struct snake_t* prev;
}snake_t;

void snake_run_game(void);

#endif
