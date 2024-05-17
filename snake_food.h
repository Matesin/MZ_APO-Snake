#ifndef __SNAKE_FOOD_H__
#define __SNAKE_FOOD_H__

#include <stdlib.h>
#include "constants.h"
#include "display_utils.h"

#define SNAKE_FOOD_SIZE 15 //will have square shape

typedef struct snake_food{
    int x;
    int y;
    int size;
    void (*change_position) (struct snake_food *self);
    void (*draw) (struct snake_food *self);
} snake_food_t;
void change_food_position(snake_food_t* self);
void draw_food(snake_food_t* self);
snake_food_t init_food();
#endif //__SNAKE_FOOD_H__
