#include "main_menu.h"
/*
Values for the main menu
TO BE CHANGED
*/
#define MM_BUTTON_COLOR {0, 0, 0} //MM for main menu
#define MM_BUTTON_TEXT_COLOR {255, 255, 255}

menu_t main_menu = {
    .title = "MAIN MENU",
    .title_color = MM_BUTTON_TEXT_COLOR,
    .title_size = 50,
    .buttons = (button_t[]) {
        {
            .text = "Start Game",
            .text_color = {255, 255, 255},
            .selected = true,
            .rectangle = {
                .start = { .x = MENU_START_X, .y = MENU_START_Y },
                .width = BUTTON_WIDTH,
                .height = BUTTON_HEIGHT,
                .color = MM_BUTTON_COLOR
            },
        },
        {
            .text = "Options",
            .selected = false,
            .rectangle = {
                .start = { .x = MENU_START_X, .y = MENU_START_Y + BUTTON_SPACING},
                .width = BUTTON_WIDTH,
                .height = BUTTON_HEIGHT,
                .color = MM_BUTTON_COLOR
            },
        },
        {
            .text = "Exit",
            .selected = false,
            .rectangle = {
                .start = { .x = MENU_START_X, .y = MENU_START_Y + 2 * BUTTON_SPACING},
                .width = BUTTON_WIDTH,
                .height = BUTTON_HEIGHT,
                .color = MM_BUTTON_COLOR
            },
        }
    },
    .num_buttons = 3,
    .selected_button = 0,
    .show_menu = show_menu
};

void show_main_menu(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes) {
    int cur_knob_value = 0;
    int prev_knob_value = 0;
    while (1){
        self->show_menu(self, graphics, fdes);
        //check for knob rotation, pseudocode below
        //cur_knob_value = get_knob_value();
        //self->selected_button = modify_while_rotating(cur_knob_value, prev_knob_value, self->selected_button, self->num_buttons);
        //prev_knob_value = cur_knob_value;
        //if (button_pressed()){
            //if (self->selected_button == 0){
                //start_game();
            //}
            //else if (self->selected_button == 1){
                //show_options();
            //}
            //else if (self->selected_button == 2){
                //exit_game();
            //}
        //}
    }

}
