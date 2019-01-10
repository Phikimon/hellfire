#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

enum {COLOR_BLACK = 0};
enum {COLOR_WHITE = 35};
enum {COLOR_NUM   = 36};

enum {MAX_TERM_WIDTH  = 155};
enum {MAX_TERM_HEIGHT = 54};

typedef int color_number;
typedef unsigned char rgb_value[3];

extern const rgb_value COLORS[COLOR_NUM];

struct terminal {
	int width, height;
	int is_fire_source_present;
	color_number** intensity;
	color_number** fire_source;
};

struct point {
	int x, y;
};

enum fire_shape {
	SHAPE_NIL = 0,
	SHAPE_LINE,
	SHAPE_PHIL,
	SHAPE_NUM
};

void term_ctor(struct terminal* term, enum fire_shape);
void term_dtor(struct terminal* term);
void term_copy(struct terminal* dst, struct terminal* src);

void term_init(void);
void term_uninit(void);

void term_set_color(color_number num);
void term_goto_xy(int x, int y);

#endif
