#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

enum {COLOR_BLACK = 0};
enum {COLOR_WHITE = 35};
enum {COLOR_NUM   = 36};

typedef int color_number;
typedef unsigned char rgb_value[3];

extern const rgb_value COLORS[COLOR_NUM];

struct terminal {
	int width, height;
	color_number** intensity;
};

void term_ctor(struct terminal* term);
void term_dtor(struct terminal* term);
void term_copy(struct terminal* dst, struct terminal* src);

void term_init(void);
void term_uninit(void);

void term_set_color(color_number num);
void term_goto_xy(int x, int y);

#endif
