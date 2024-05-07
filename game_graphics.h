#ifndef __GAME_GRAPHICS_H__
#define __GAME_GRAPHICS_H__
#include <stdint.h>
#include <stdlib.h>
#include "graphic_structures.h"

void init_graphics(graphics_object_t *self);
void display(graphics_object_t *self);
void draw_line(graphics_object_t *self, line_t line, color_t color);
void clear_screen(graphics_object_t *self, color_t color);
#endif // __GAME_GRAPHICS_H__