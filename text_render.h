#ifndef __TEXT_RENDER_H__
#define __TEXT_RENDER_H__
#include "font_types.h"
#include "graphic_structures.h"
#include <stdint.h>
void draw_char(graphics_object_t *self, point_t point, char ch, color_t color, font_descriptor_t *fdes);
void draw_string(graphics_object_t *self, point_t point, char *string, color_t color, font_descriptor_t* fdes);
int char_width(font_descriptor_t* fdes, int ch);
#endif // __TEXT_RENDER_H__
