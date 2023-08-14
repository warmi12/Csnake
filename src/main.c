#include <ncurses.h>

#include "screen.h"
#include "menu.h"

int main(){

	screen_init();
	menu();
	
        return 0;
}
