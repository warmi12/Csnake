#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <ncurses.h>

#include "sigterm.h"

void sigterm_init(void){
	
	struct sigaction action;
      	memset(&action, 0, sizeof(struct sigaction));
        action.sa_handler = term_snake;
        sigaction(SIGINT, &action, NULL);
}

void term_snake(int signum){
	
	UNUSED(signum);	
	endwin();
}

