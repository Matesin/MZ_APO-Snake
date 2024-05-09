#ifndef __INGAME_MENU_H__
#define __INGAME_MENU_H__
#include "menu.h"
#include "game.h"
void show_ingame_menu(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes);
void resume_game(game_t *game, graphics_object_t* graphics, font_descriptor_t* fdes);
void show_main_menu(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes);
void exit_game();
#endif // __INGAME_MENU_H__