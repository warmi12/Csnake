#ifndef SCREEN_H
#define SCREEN_H

#define MIN_ROW_SIZE 50
#define MIN_COL_SIZE 50

typedef struct{

	uint16_t max_row;
	uint16_t max_col; 
	uint16_t center_row;
	uint16_t center_col; 
}screen_params_t;

extern screen_params_t screen_params;

void screen_init(void);

#endif
