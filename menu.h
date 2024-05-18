#ifndef __MENU__
#define __MENU__
#include <stdlib.h>
#include "display_utils.h"
#include "text_render.h"

typedef struct button{
    _Bool selected;
    rectangle_t rectangle;
    text_t button_text;
    unsigned short cur_color;
    unsigned short base_color;
    unsigned short selected_color;
    void (*draw) (struct button* self);
} button_t;

typedef struct menu{
    int padding;
    text_t title;
    unsigned short title_color;
    unsigned short button_base_color;
    unsigned short button_selected_color;
    unsigned short button_text_color;
    button_t *buttons;
    short num_buttons;
    short selected_button;
    void (*show) (struct menu* self);
    void (*update) (struct menu* self, short selected_button); 
} menu_t;

void draw_button(button_t* self);
void draw_menu(menu_t* self);
void update_menu(menu_t* self, short selected_button)

#endif // MENU