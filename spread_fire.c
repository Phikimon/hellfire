#include "spread_fire.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/* Boring static picture */
color_number dummy_spread_fire(struct terminal* term, int x, int y)
{
	assert(y != 0);

	return (term->intensity[x][y - 1] == COLOR_BLACK) ?
	        COLOR_BLACK :
	       (term->intensity[x][y - 1] - 1);
}

/* Sets fire depending on fire intensity in triangle
   below the cell, random value and the height of the
   cell. More unnamed constants to the god of contants! */
color_number fancy_spread_fire(struct terminal* term, int x, int y)
{
	assert(y != 0);

	const int triangle_size = 4;
	const int enough_intensity = 10 * COLOR_WHITE;

	/* Initialize randomizer */
	static int is_first_call = 1;
	if (is_first_call == 1) {
		srand(time(NULL));
		is_first_call = 0;
	}

	/* Sum up the intensity */
	int intensity_sum = 0;
	for (int cur_x = x - triangle_size; cur_x <= x + triangle_size; cur_x++) {
		if ((cur_x < 0) || (cur_x > term->width - 1))
			continue;
		for (int cur_y = y - triangle_size; cur_y <= y - abs(x - cur_x); cur_y++) {
			if ((cur_y < 0) || (cur_y > term->height - 1) || ((cur_x == x) && (cur_y == y)))
				continue;
			intensity_sum += term->intensity[cur_x][cur_y];
		}
	}
	intensity_sum = (intensity_sum > enough_intensity) ? enough_intensity : intensity_sum;

	/* No self-ignition */
	if (intensity_sum == 0)
		return COLOR_BLACK;

	double prob           = (double) rand()        / RAND_MAX;
	double height_prob    = (double) y             / term->height;
	double intensity_prob = (double) intensity_sum / enough_intensity;

	/* Enjoy your play! */
	double res = sin(prob + pow(intensity_prob, 0.5) - pow(height_prob, 0.4) * 1.5);

	res = (res < 0) ? 0 : res;

	return res * COLOR_WHITE;
}

color_number test_spread_fire(struct terminal* term, int x, int y)
{
	return COLOR_BLACK;
}
