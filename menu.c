#include "menu.h"

#include <stdint.h>
#include <stdio.h>

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;

void show_menu(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes) {
    for (int i = 0; i < self->num_buttons; ++i) {
        draw_button(&self->buttons[i], graphics, fdes);
    }
}