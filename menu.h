#ifndef __MENU__
#define __MENU__
#include "menu_graphics.h"

typedef struct menu{
    button_t *buttons;
    int num_buttons;
    int selected_button;
    void (*show_menu)(struct menu *self, graphics_object_t* graphics, font_descriptor_t* fdes);
} menu_t;

void show_menu(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes);

#endif // MENU