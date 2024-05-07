#ifndef __MENU_GRAPHICS_H__
#define __MENU_GRAPHICS_H__
#include <stdint.h>
#include <stdbool.h>
#include "graphic_structures.h"
#include "font_types.h"

typedef struct rectangle{
    point_t start;
    int width;
    int height;
    color_t color;
} rectangle_t;
typedef struct button{
    char* text;
    bool selected;
    rectangle_t rectangle;
    color_t text_color;
    color_t button_color;
    void (*draw_button)(struct button *self);
    void (*draw_button_outline)(struct button *self);
} button_t;
typedef struct button_outline{
    //always draw first, under the respective button
    rectangle_t rectangle;
    color_t outline_color;
    void (*draw_outline)(struct button_outline *self);
} button_outline_t;

void set_button_text(button_t *self, char* text);
void draw_rectangle(rectangle_t *self);
void draw_button(button_t *self, graphics_object_t* graphics, font_descriptor_t* fdes);
void draw_button_outline(button_t *self, graphics_object_t* graphics);
#endif //__MENU_GRAPHICS