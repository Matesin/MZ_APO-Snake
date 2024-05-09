#ifndef __MENU__
#define __MENU__
#include "menu_graphics.h"
#include "game.h"
#include <stdlib.h>
#define SENSITIVITY 3
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING BUTTON_HEIGHT + 20
#define BUTTON_TEXT_SIZE BUTTON_HEIGHT / 2
// starting position - TO BE CHANGED
#define MENU_START_X 100 //start x position of the first button 
#define MENU_START_Y 100 //start y position of the first button
#define TEXT_START_X MENU_START_X + 10 //start x position of the text in the button
#define TEXT_START_Y MENU_START_Y + 10 //start y position of the text in the button
typedef struct menu{
    char* title;
    color_t title_color;
    int title_size;
    button_t *buttons;
    int num_buttons;
    int selected_button;
    game_t *game_state;
    void (*show_menu)(struct menu *self, graphics_object_t* graphics, font_descriptor_t* fdes, game_t* game);
} menu_t;

void show_menu(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes, game_t *game_state);
int modify_while_rotating(int cur_value, int prev_value, int action_num, int upper_range);

#endif // MENU