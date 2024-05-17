#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__
#include <stdlib.h>
#include <stdint.h>
#include "display_utils.h"
#include "knob.h"
#define SNAKE_SQUARE_SIZE 25
#define SNAKE_SPEED 5
#define SNAKE_START_LENGTH 3
#define SNAKE_MAX_LENGTH 50

enum Direction{
  UP,
  RIGHT,
  DOWN,
  LEFT,
};


typedef struct snake_square{
  //top left pixel of the square
  int x_coord;
  int y_coord;
} snake_sq_t;

typedef struct snake {
  snake_sq_t* squares;
  int speed;
  char direction;
  int length;
  int color;
  void (*update)(struct snake *self, knob_t* k);
  void (*draw)(struct snake *self, unsigned char* parlcd_mem_base);
} snake_t;
void draw_snake(snake_t *self, unsigned char *parlcd_mem_base);
void update_snake(snake_t* self, knob_t* k);

#endif //__GAME_CONSTANTS_H__