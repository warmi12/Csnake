#ifndef MENU_H
#define MENU_H

#define MIN_ROW_SIZE 50
#define MIN_COL_SIZE 50
#define MENU_SIZE 5
#define MENU_MAX_STRING_SIZE 20
#define MENU_ROW_SPACE 1

typedef enum {
	INIT,
	DRAW,
	SELECT,
	IDLE
} menu_state_e;

void get_screen_size(void);

void menu_init(void);

void menu_draw(void);

void menu_set_next_state(menu_state_e menu_next_state);

void menu(void);


#endif
