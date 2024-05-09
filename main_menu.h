#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__
#include "menu.h"
#include "game.h"
/*
Function to show the main menu, to be defined in main_menu.c
*/
void show_main_menu(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes, game_t *game);
void start_game(game_t *game, graphics_object_t* graphics, font_descriptor_t* fdes);
void show_options(menu_t *self, graphics_object_t* graphics, font_descriptor_t* fdes);
void exit_game();

#endif // __MAIN_MENU_H__
