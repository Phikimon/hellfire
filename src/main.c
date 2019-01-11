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
	term_toggle_fire_source(&term);
}

int main(void)
{
	sigset_t sigs;
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGINT);

	term_init();
	term_ctor(&term, SHAPE_LINE);

	signal(SIGINT, int_handler);
	do {
		sigprocmask(SIG_BLOCK, &sigs, NULL);
		flame_evolution(&term, fancy_spread_fire);
		flame_render(&term);
		sigprocmask(SIG_UNBLOCK, &sigs, NULL);
		usleep(60000);
	} while (is_there_any_flame(&term));

	term_dtor(&term);
	term_uninit();
	usleep(500000);
	return 0;
}
