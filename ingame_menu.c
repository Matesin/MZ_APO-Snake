#include "ingame_menu.h"

#define IGM_BUTTON_COLOR {0, 0, 0} //IGM for in-game menu
#define IGM_BUTTON_TEXT_COLOR {255, 255, 255}
menu_t ingame_menu = {
    .title = "PAUSED",
    .title_color = IGM_BUTTON_TEXT_COLOR,
    .title_size = 50,
    .buttons = (button_t[]){
        {
            .text = "Resume",
            .text_color = IGM_BUTTON_TEXT_COLOR,
            .text_size = BUTTON_TEXT_SIZE,
            .rectangle = {
                .start = { .x = MENU_START_X, .y = MENU_START_Y },
                .width = BUTTON_WIDTH,
                .height = BUTTON_HEIGHT,
                .color = IGM_BUTTON_COLOR,
            },
        },
        {
            .text = "Main Menu",
            .text_color = IGM_BUTTON_TEXT_COLOR,
            .text_size = BUTTON_TEXT_SIZE,
            .rectangle = {
                .start = { .x = MENU_START_X, .y = MENU_START_Y + BUTTON_SPACING},
                .width = BUTTON_WIDTH,
                .height = BUTTON_HEIGHT,
                .color = IGM_BUTTON_COLOR
            },
        }
        ,
        {
            .text = "Exit",
            .text_color = IGM_BUTTON_TEXT_COLOR,
            .text_size = BUTTON_TEXT_SIZE,
            .rectangle = {
                .start = { .x = MENU_START_X, .y = MENU_START_Y + 2 * BUTTON_SPACING},
                .width = BUTTON_WIDTH,
                .height = BUTTON_HEIGHT,
                .color = IGM_BUTTON_COLOR
            },
        }
    },
    .num_buttons = 3,
    .selected_button = 0,
    .show_menu = show_ingame_menu,
    .game_state = NULL
};

void show_ingame_menu(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes, game_t *game){
    // Function implementation goes here
    self->game_state = game;
    while (1){
        self->show_menu(self, graphics, fdes, game);
        //check for knob rotation, pseudocode below
        //cur_knob_value = get_knob_value();
        //self->selected_button = modify_while_rotating(cur_knob_value, prev_knob_value, self->selected_button, self->num_buttons);
        //prev_knob_value = cur_knob_value;
        //if (button_pressed()){
            //if (self->selected_button == 0){
                //resume_game(game, graphics, fdes);
            //}
            //else if (self->selected_button == 1){
                //show_main_menu(main_menu, graphics, fdes);
            //}
            //else if (self->selected_button == 2){
                //exit_game();
        //}
    }
}
void resume_game(game_t *game, graphics_object_t* graphics){
    //resume the game
    game_loop(graphics, game);
}
void show_main_menu(menu_t *main_menu, graphics_object_t* graphics, font_descriptor_t* fdes){
    //show the main menu
    main_menu->show_menu(main_menu, graphics, fdes, NULL);
}
void exit_game(){
    //exit the game
    exit(0);
}