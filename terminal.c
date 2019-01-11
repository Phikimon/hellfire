#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "terminal.h"

#define CALLOC(VAR, TYPE, N) \
do { \
	VAR = (TYPE)calloc(N, sizeof(*(VAR))); \
	assert(VAR); \
} while (0)

#define FREE(VAR) \
do { \
	free(VAR); \
	VAR = NULL; \
} while (0)

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

	term->width  = (w.ws_col > MAX_TERM_WIDTH) ?
			MAX_TERM_WIDTH :
			w.ws_col;
	term->height = (w.ws_row > MAX_TERM_HEIGHT) ?
			MAX_TERM_HEIGHT :
			w.ws_row;
}

void term_init(void)
{
	term_hide_cursor();
	term_clear();
}

void term_uninit(void)
{
	putchar('\n');
	term_show_cursor();
}

static void parse_fire_string(struct terminal* term,
				const char* fire_string,
				int string_num)
{
	int string_len = strlen(fire_string);
	assert(string_len == MAX_TERM_WIDTH);
	int y = (double)string_num * term->height / MAX_TERM_HEIGHT;

	for (int i = 0; i < string_len; i++) {
		int x = (double)i * term->width / MAX_TERM_WIDTH;
		switch (fire_string[i])
		{
			case '@':
				term->fire_source[x][y] = COLOR_WHITE;
				break;
			case '-':
				term->fire_source[x][y] = COLOR_BLACK;
				break;
			default:
				assert(0);
		}
	}
}

void term_toggle_fire_source(struct terminal* term)
{
	assert(term);
	term_set_fire_source(term, (term->current_shape + 1) % SHAPE_NUM);
}

void term_set_fire_source(struct terminal* term, enum fire_shape shape)
{
	assert(term);
	assert(shape >= 0 && shape < SHAPE_NUM);
	int string_num = MAX_TERM_HEIGHT;
	term->current_shape = shape;

#define $(string) \
	do { \
		string_num--; \
		parse_fire_string(term, string, string_num); \
	} while (0)

	switch (shape)
	{
		case SHAPE_PHIL:
#define SHAPE_PHIL
#include "shapes.lst"
#undef SHAPE_PHIL
			break;
		case SHAPE_LINE:
#define SHAPE_LINE
#include "shapes.lst"
#undef SHAPE_LINE
			break;
		case SHAPE_NIL:
			for (int i = 0; i < term->width; i++)
				memset(term->fire_source[i] ,
					COLOR_BLACK,
					term->height * sizeof(term->fire_source[i][0]));

			string_num = 0;
			break;
		default: assert(0);
	}
	assert(string_num == 0);

#undef $
}

void term_ctor(struct terminal* term, enum fire_shape shape)
{
	assert(term);
	term_get_dimensions(term);

	/* Will be initialized with black color, because COLOR_BLACK == 0 */
	CALLOC(term->intensity,   color_number**, term->width);
	CALLOC(term->fire_source, color_number**, term->width);
	for (int i = 0; i < term->width; i++) {
		CALLOC(term->intensity[i],   color_number*, term->height);
		CALLOC(term->fire_source[i], color_number*, term->height);
	}

	term_set_fire_source(term, shape);
}

void term_dtor(struct terminal* term)
{
	assert(term);
	for (int i = 0; i < term->width; i++) {
		FREE(term->intensity[i]);
		FREE(term->fire_source[i]);
	}
	FREE(term->intensity);
	FREE(term->fire_source);

	term->width = term->height = 0;
}

void term_copy(struct terminal* dst, struct terminal* src)
{
	assert(dst->width == src->width && dst->height == src->height);

	for (int x = 0; x < dst->width; x++)
		memcpy(dst->intensity[x],   src->intensity[x],   dst->height * sizeof(dst->intensity[x][0]));
}
