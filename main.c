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
	static int tumbler = 1;
	if (tumbler)
		flame_stop(&term);
	else
		flame_start(&term);
	tumbler ^= 1;
}

int main(void)
{
	term_init();
	term_ctor(&term);

	flame_start(&term);
	signal(SIGINT, int_handler);
	while (is_there_any_flame(&term)) {
		flame_evolution(&term, fancy_spread_fire);
		flame_render(&term);
		usleep(60000);
	}

	term_dtor(&term);
	term_uninit();
	usleep(500000);
	return 0;
}
