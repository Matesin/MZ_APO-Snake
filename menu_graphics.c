#include "menu_graphics.h"
#include "text_render.h"
#include "display_utils.h"
#include "graphic_structures.h"

// Draw the button
void draw_button(button_t *self, graphics_object_t* graphics, font_descriptor_t* fdes){
    if (self->selected){
        draw_button_outline(self, graphics);
    }
    draw_rectangle(&self->rectangle);
    draw_string(graphics, self->rectangle.start, self->text, self->text_color, fdes);
}
// Draw the outline of the button
void draw_button_outline(button_t *self, graphics_object_t* graphics){
    button_outline_t outline = {
        .rectangle = {
            .start = {
                .x = self->rectangle.start.x - 1,
                .y = self->rectangle.start.y - 1
            },
            .width = self->rectangle.width + 2,
            .height = self->rectangle.height + 2,
            //set to white
            .color = {
                .red = 255,
                .green = 255,
                .blue = 255
            }
        },
    };
    draw_rectangle(&outline.rectangle);
}
// Set the text of the button
void set_button_text(button_t *self, char* text){
    self->text = text;
}
