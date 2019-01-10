#include "flame.h"

#include <stdio.h>
#include <assert.h>

void flame_start(struct terminal* term)
{
	assert(term);
	term->is_fire_source_present = 1;
}

void flame_stop(struct terminal* term)
{
	assert(term);
	term->is_fire_source_present = 0;
}

void flame_render(struct terminal* term)
{
	assert(term);
	term_goto_xy(0, 0);
	for (int y = term->height - 1; y >= 0; y--) {
		for (int x = 0; x < term->width; x++) {
			term_set_color(term->intensity[x][y]);
			putchar(' ');
		}
		if (y != 0)
			putchar('\n');
	}
}

static int is_fire_source_cell(struct terminal* term, int x, int y)
{
	return (term->is_fire_source_present == 1) && (term->fire_source[x][y] != COLOR_BLACK);
}

void flame_evolution(struct terminal* term, spread_fire_func spread_fire)
{
	assert(term);
	struct terminal tmp_term = {0};
	term_ctor(&tmp_term, SHAPE_NIL);

	for (int x = 0; x < term->width; x++)
		for (int y = 0; y < term->height; y++) {
			if (is_fire_source_cell(term, x, y))
				tmp_term.intensity[x][y] = term->fire_source[x][y];
			else
				tmp_term.intensity[x][y] = spread_fire(term, x, y);
			assert(tmp_term.intensity[x][y] >= 0 && tmp_term.intensity[x][y] < COLOR_NUM);
		}

	term_copy(term, &tmp_term);
	term_dtor(&tmp_term);
}

int is_there_any_flame(struct terminal* term)
{
	assert(term);
	for (int x = 0; x < term->width; x++)
		for (int y = 0; y < term->height; y++)
			if (term->intensity[x][y] != COLOR_BLACK)
				return 1;

	return 0;
}
