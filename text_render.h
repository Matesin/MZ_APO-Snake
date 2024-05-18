#ifndef __TEXT_RENDER_H__
#define __TEXT_RENDER_H__
#include "font_types.h"
#include "constants.h"
#include <stdint.h>

typedef struct text{
    char* text;
    int scale;
    int start_x;
    int start_y;
    unsigned short color;
    void (*draw)(struct text* self);
} text_t;

void draw_char(int x, int y, char ch, unsigned short color, int scale);
int char_width(int ch);
text_t new_text(int x, int y, char* text, unsigned short color, int scale);
#endif // __TEXT_RENDER_H__
