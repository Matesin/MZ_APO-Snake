#ifndef __GAME_GRAPHICS_H__
#define __GAME_GRAPHICS_H__
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    point_t start;
    point_t end;
} line_t;

typedef struct graphics_object{
    void (*init) (struct graphics_object *self);
    void (*draw_pixel) (struct graphics_object *self, point_t point, color_t color);
    void (*draw_line) (struct graphics_object *self, line_t line, color_t color);
    void (*clear_screen) (struct graphics_object *self, color_t color);
    void (*display) (struct graphics_object *self);

    uint16_t frame_buffer;
    int width;
    int height;
} graphics_object_t;

void init_graphics(graphics_object_t *self);
void draw_pixel(graphics_object_t *self, point_t point, color_t color);
void display(graphics_object_t *self);
void draw_line(graphics_object_t *self, line_t line, color_t color);
void clear_screen(graphics_object_t *self, color_t color);
#endif // __GAME_GRAPHICS_H__