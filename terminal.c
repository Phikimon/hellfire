#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "terminal.h"

const rgb_value COLORS[COLOR_NUM] =
{
	{  0,   0,   0},
	{ 30,   7,   7},
	{ 45,  15,   7},
	{ 71,  15,   7},
	{ 86,  22,   7},
	{102,  30,   7},
	{119,  30,   7},
	{142,  38,   7},
	{158,  45,   7},
	{175,  63,   7},
	{191,  71,   7},
	{198,  71,   7},
	{221,  79,   7},
	{221,  86,   7},
	{221,  86,   7},
	{214,  94,   7},
	{214, 102,  15},
	{206, 112,  15},
	{206, 119,  15},
	{206, 127,  15},
	{206, 135,  22},
	{198, 135,  22},
	{198, 142,  22},
	{198, 150,  30},
	{191, 158,  30},
	{191, 158,  30},
	{191, 165,  38},
	{191, 165,  38},
	{191, 175,  45},
	{183, 175,  45},
	{183, 183,  45},
	{183, 183,  56},
	{206, 206, 112},
	{221, 221, 158},
	{239, 239, 198},
	{255, 255, 255},
};

void term_set_color(color_number num)
{
	assert(num >= 0 && num < COLOR_NUM);
	printf("\033[48;2;%d;%d;%dm",
		COLORS[num][0], COLORS[num][1], COLORS[num][2]);
}

void term_goto_xy(int x, int y)
{
	assert(x >= 0 && y >= 0);
	printf("\033[%d;%dH", x, y);
}

static void term_clear(void)
{
	printf("\033[H\033[J");
}

static void term_hide_cursor(void)
{
	printf("\033[?25l");
}

static void term_show_cursor(void)
{
	printf("\033[?25h");
}

static void term_get_dimensions(struct terminal* term)
{
	assert(term);
	struct winsize w = {0};
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	term->width  = w.ws_col;
	term->height = w.ws_row;
}

void term_init(void)
{
	term_hide_cursor();
	term_clear();
}

void term_uninit(void)
{
	term_show_cursor();
}

void term_ctor(struct terminal* term)
{
	assert(term);
	term_get_dimensions(term);

	/* Will be initialized with black color, because COLOR_BLACK == 0 */
	term->intensity = (color_number**)calloc(term->width, sizeof(*term->intensity));
	assert(term->intensity);
	for (int i = 0; i < term->width; i++) {
		term->intensity[i] = (color_number*)calloc(term->height, sizeof(*term->intensity[i]));
		assert(term->intensity[i]);
	}
}

void term_dtor(struct terminal* term)
{
	assert(term);
	for (int i = 0; i < term->width; i++) {
		free(term->intensity[i]);
		term->intensity[i] = NULL;
	}
	free(term->intensity);
	term->intensity = NULL;

	term->width = term->height = 0;
}

void term_copy(struct terminal* dst, struct terminal* src)
{
	assert(dst->width == src->width && dst->height == src->height);

	for (int x = 0; x < dst->width; x++)
		for (int y = 0; y < dst->height; y++)
			dst->intensity[x][y] = src->intensity[x][y];
}
