#include "game_graphics.h"

void init_graphics(graphics_object_t *self){
    self->frame_buffer = 0;
    self->width = 0;
    self->height = 0;

}
void draw_pixel(graphics_object_t *self, point_t p, color_t c){
    if (p.x >= 0 && p.x < self->width && p.y >= 0 && p.y < self->height) {
        int index = ((p.y * self->width) + p.x) * 3;
        self->frame_buffer[&index] = c.red;
        self->frame_buffer[&index + 1] = c.green;
        self->frame_buffer[&index + 2] = c.blue;
    }
}
void display(graphics_object_t *self){
    for (uint16_t y = 0; y < self->height; y++) {
        for (uint16_t x = 0; x < self->width; x++) {
        }
    }

}
void draw_line(graphics_object_t *self, line_t line, color_t color){
    //implement Bresenham's line algorithm
    int dx = abs(line.end.x - line.start.x);
    int dy = abs(line.end.y - line.start.y);
    int sx = line.start.x < line.end.x ? 1 : -1;
    int sy = line.start.y < line.end.y ? 1 : -1;
    int err = dx - dy;
    int e2;
    while (1) {
        draw_pixel(self, line.start, color);
        if (line.start.x == line.end.x && line.start.y == line.end.y) {
            break;
        }
        e2 = 2 * err;
        if (e2 > -dy) {
            err = err - dy;
            line.start.x = line.start.x + sx;
        }
        if (e2 < dx) {
            err = err + dx;
            line.start.y = line.start.y + sy;
        }
    }
}
void clear_screen(graphics_object_t *self, color_t color){
    for (uint16_t y = 0; y < self->height; y++) {
        for (uint16_t x = 0; x < self->width; x++) {
            point_t p = {x, y};
            draw_pixel(self, p, color);
        }
    }
}
