/**
 * @file display_utils.c
 * @brief This file contains functions for handling the display.
 */

#include "display_utils.h"

/**
 * @brief Initializes the memory base for the SPILED.
 * @return A pointer to the memory base.
 */

unsigned char* init_mem_base(){
  unsigned char *mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (mem_base == NULL) {
    fprintf(stderr, "Error: Unable to map physical address\n");
    exit(1);
  }
  return mem_base;
}

/**
 * @brief Initializes the memory base for the display.
 * @return A pointer to the memory base.
 */

unsigned char* init_parlcd_mem_base(){
  unsigned char *parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL) {
    fprintf(stderr, "Error: Unable to map physical address\n");
    exit(1);
  }
  return parlcd_mem_base;
}

/**
 * @brief Draws a pixel on the display.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 */

void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}

/**
 * @brief Draws a pixel on the display with a specified scale.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 * @param scale The scale of the pixel.
 */

void draw_pixel_big(int x, int y, unsigned short color, int scale) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel(x+i, y+j, color);
    }
  }
}

/**
 * @brief Clears the screen.
 * @param parlcd_mem_base The memory base for the display.
 * @param fb The framebuffer.
 */

void clear_screen(unsigned char *parlcd_mem_base, unsigned short* fb){
  int ptr = 0;
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
  }
}

/**
 * @brief Initializes the framebuffer.
 * @param fb The framebuffer.
 */

void reset_fb(unsigned short* fb, unsigned short color){
  int ptr = 0;
  for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=color;
  }
}

/**
 * @brief Clears the screen at the end of the game.
 * @param parlcd_mem_base The memory base for the display.
 */

void endgame_clear_screen(unsigned char *parlcd_mem_base){
  int ptr;
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
    parlcd_write_data(parlcd_mem_base, 0);
  }
}

/**
 * @brief constructor for a rectangle.
 * @param fb The framebuffer.
 */

rectangle_t new_rectangle(int x, int y, int width, int height, unsigned short color){
  rectangle_t r;
  r.x = x;
  r.y = y;
  r.width = width;
  r.height = height;
  r.color = color;
  r.draw = draw_rectangle;
  return r;
}

/**
 * @brief Draws a rectangle on the display.
 * @param self The rectangle to draw.
 */


void draw_rectangle(rectangle_t* self){
 int i,j;
  for (i=0; i<self->width; i++) {
    for (j=0; j<self->height; j++) {
      draw_pixel(self->x+i, self->y+j, self->color);
    }
  }
}
