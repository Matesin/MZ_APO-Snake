/**
 * @file game.h
 * @brief This file contains the declarations of functions for the game logic.
 */

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
//--------------------FUNCTION--------------------
/**
 * @brief Checks for collision between a snake and food.
 * 
 * @param snake The snake to check for collision.
 * @param food The food to check for collision.
 * @return Returns TRUE if a collision is detected, FALSE otherwise.
 */
_Bool check_food_collision(snake_t* snake, snake_food_t* food);
//--------------------FUNCTION--------------------
/**
 * @brief Checks for collision between a snake and itself.
 * 
 * @param snake The snake to check for collision.
 * @return Returns TRUE if a collision is detected, FALSE otherwise.
 */
_Bool check_snake_collision(snake_t* snake);
//--------------------FUNCTION--------------------
/**
 * @brief Checks if two rectangles intersect.
 * 
 * @param x1, y1, w1, h1 The coordinates and dimensions of the first rectangle.
 * @param x2, y2, w2, h2 The coordinates and dimensions of the second rectangle.
 * @return Returns TRUE if the rectangles intersect, FALSE otherwise.
 */
_Bool intersects(int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2);
//--------------------FUNCTION--------------------
/**
 * @brief Converts a short to a char array.
 * 
 * @param num The short to convert.
 * @param result The resulting char array.
 */
void short_to_char(short num, char* result);
//--------------------FUNCTION--------------------
/**
 * @brief Starts the game.
 * 
 * @param parlcd_mem_base The memory base for the parallel LCD.
 * @param mem_base The memory base for the game.
 * @param multiplayer A flag indicating if the game is multiplayer.
 */
void play_game(unsigned char *parlcd_mem_base, unsigned char *mem_base, _Bool multiplayer);
//--------------------FUNCTION--------------------
/**
 * @brief Draws the score of the snakes.
 * 
 * @param snakes The snakes to draw the score for.
 * @param num_snakes The number of snakes.
 */
void draw_score(snake_t* snakes, short num_snakes);

#endif //__GAME_H__