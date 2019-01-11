#ifndef FLAME_H_INCLUDED
#define FLAME_H_INCLUDED

#include "terminal.h"
#include "spread_fire.h"

void flame_start       (struct terminal* term);
void flame_stop        (struct terminal* term);

void flame_render      (struct terminal* term);
void flame_evolution   (struct terminal* term,
			spread_fire_func spread_fire);

int  is_there_any_flame(struct terminal* term);

#endif
