#define _BSD_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "terminal.h"
#include "flame.h"

struct terminal term = {0};

void int_handler(int dummy)
{
	static int toggle_switch = 1;
	if (toggle_switch)
		flame_stop(&term);
	else
		flame_start(&term);
	toggle_switch ^= 1;
}

int main(void)
{
	term_init();
	term_ctor(&term, SHAPE_PHIL);

	flame_start(&term);
	signal(SIGINT, int_handler);
	do {
		flame_evolution(&term, fancy_spread_fire);
		flame_render(&term);
		usleep(60000);
	} while (is_there_any_flame(&term));

	term_dtor(&term);
	term_uninit();
	usleep(500000);
	return 0;
}
