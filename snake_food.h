/**
 * @file snake_food.h
 * @brief This file contains the declarations of functions and structures for handling the snake food.
 */

#ifndef __SNAKE_FOOD_H__
#define __SNAKE_FOOD_H__

#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "display_utils.h"
//--------------------STRUCTURE--------------------
/**
 * @brief A structure representing a piece of snake food.
 */
typedef struct snake_food{
    int x; ///< The x-coordinate of the food.
    int y; ///< The y-coordinate of the food.
    int size; ///< The size of the food.
    int color; ///< The color of the food.
    void (*change_position) (struct snake_food *self); ///< A function pointer to change the position of the food.
    void (*draw) (struct snake_food *self, unsigned char *parlcd_mem_base); ///< A function pointer to draw the food.
} snake_food_t;
//--------------------FUNCTION--------------------
/**
 * @brief Changes the position of the food.
 * @param self A pointer to the food.
*/
void change_food_position(snake_food_t* self);
//--------------------FUNCTION--------------------
/**
 * @brief Draws the food.
 * @param self A pointer to the food.
 * @param parlcd_mem_base A pointer to the memory base for the parallel LCD.
 */
void draw_food(snake_food_t* self, unsigned char *parlcd_mem_base); 
//--------------------CONSTRUCTOR--------------------
/**
 * @brief Initializes the food.
 * @param color The color of the food.
 * @return The initialized food.
 */
snake_food_t init_food(unsigned short color); 

#endif //__SNAKE_FOOD_H__