#ifndef MENU_H
#define MENU_H

#define MIN_ROW_SIZE 50
#define MIN_COL_SIZE 50
#define MENU_SIZE 4
#define MENU_MAX_STRING_SIZE 20
#define MENU_ROW_SPACE 1
#define KEY_MY_ENTER 10

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

void menu_highlight_row(uint16_t row);

void menu_unhighlight_row(uint16_t row);

void menu_button_process(int button);

void menu(void);


#endif
