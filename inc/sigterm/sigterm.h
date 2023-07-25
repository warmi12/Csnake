#ifndef SIGTERM_H
#define SIGTERM_H

#define UNUSED(x) (void)(x)

void sigterm_init(void);

void term_snake(int signum);

#endif

