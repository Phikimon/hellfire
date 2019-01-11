#ifndef SPREAD_FIRE_H
#define SPREAD_FIRE_H

#include "terminal.h"

typedef color_number (*spread_fire_func)(struct terminal* term, int x, int y);

/* Boring static picture */
color_number dummy_spread_fire(struct terminal* term, int x, int y);

/* Sets fire depending on fire intensity in triangle
   below the cell, random value and the height of the
   cell */
color_number fancy_spread_fire(struct terminal* term, int x, int y);

/* Used for experiments */
color_number test_spread_fire(struct terminal* term, int x, int y);

#endif
