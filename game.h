#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>
#include "serialize_lock.h"
#include "font_types.h"
#include "display_utils.h"
#include "colors.h"
#include "snake.h"
#include "knob.h"
#include "snake_food.h"
#include "led_utils.h"
#include "text_render.h" //for displaying score
#include "menu.h" //for endgame screen


_Bool check_food_collision(snake_t* snake, snake_food_t* food);
_Bool check_snake_collision(snake_t* snake);
_Bool intersects(int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2);
void short_to_char(short num, char* result);
void play_game(unsigned char *parlcd_mem_base, unsigned char *mem_base, _Bool multiplayer);
void draw_score(snake_t* snakes, short num_snakes);
#endif //__GAME_H__