/**
 * @file snake.h
 * @brief This file contains the declarations of functions and structures for handling the snake.
*/

#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__
#include <stdlib.h>
#include <stdint.h>
#include "display_utils.h"
#include "constants.h"
#include "knob.h"
#include "colors.h"

//--------------------STRUCTURE--------------------
/**
 * @brief A structure representing a square of the snake.
 */
typedef struct snake_square{
  //top left pixel of the square
  int x_coord;
  int y_coord;
} snake_sq_t;
//--------------------STRUCTURE--------------------
/**
 * @brief A structure representing the snake.
 */
typedef struct snake {
  snake_sq_t* squares;
  int square_size;
  char direction;
  int length;
  int color;
  short score;
  void (*update)(struct snake *self, knob_t* k);
  void (*draw)(struct snake *self, unsigned char* parlcd_mem_base);
} snake_t;
//--------------------FUNCTION--------------------
/**
 * @brief Draws the snake.
 * @param self A pointer to the snake.
 * @param parlcd_mem_base A pointer to the memory base for the parallel LCD.
*/
void draw_snake(snake_t *self, unsigned char *parlcd_mem_base);
//--------------------FUNCTION--------------------
/**
 * @brief Updates the snake.
 * @param self A pointer to the snake.
 * @param k A pointer to the knob.
*/
void update_snake(snake_t* self, knob_t* k);
//--------------------FUNCTION--------------------
/**
 * @brief Updates the position of the snake.
 * @param self A pointer to the snake.
*/
void update_snake_pos(snake_t* self);
//--------------------FUNCTION--------------------
/**
 * @brief Updates the direction of the snake.
 * @param self A pointer to the snake.a
 * @param k A pointer to the knob.
*/
void update_snake_dir(snake_t* self, knob_t* k);
//--------------------CONSTRUCTOR--------------------
snake_t init_snake(int color, int direction);

#endif //__GAME_CONSTANTS_H__