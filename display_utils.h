/**
 * @file display_utils.h
 * @brief This file contains the declarations of functions and structures for handling the display.
 */

#ifndef __DISPLAY_UTILS_H__
#define __DISPLAY_UTILS_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "constants.h"
#include "mzapo_parlcd.h"
#include "colors.h"
//--------------------STRUCTURE--------------------
/**
 * @brief A structure representing a rectangle.
 */
typedef struct rectangle{
    int x; ///< The x-coordinate of the rectangle.
    int y; ///< The y-coordinate of the rectangle.
    int width; ///< The width of the rectangle.
    int height; ///< The height of the rectangle.
    unsigned short color; ///< The color of the rectangle.
    void (*draw) (struct rectangle* self); ///< A function pointer to draw the rectangle.
} rectangle_t;

extern font_descriptor_t* fdes; ///< A pointer to the font descriptor.
extern unsigned short* fb; ///< A pointer to the framebuffer.
//--------------------FUNCTION--------------------
/**
 * @brief Initializes the memory base for the display.
 * @return The memory base for the display.
 */
unsigned char* init_mem_base();
//--------------------FUNCTION--------------------
/**
 * @brief Initializes the memory base for the parallel LCD.
 * @return The memory base for the parallel LCD.
 */
unsigned char* init_parlcd_mem_base();
//--------------------FUNCTION--------------------
/**
 * @brief Draws a pixel at the given coordinates with the given color.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 */
void draw_pixel(int x, int y, unsigned short color); 
//--------------------FUNCTION--------------------
/**
 * @brief Draws a larger pixel at the given coordinates with the given color and scale.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 * @param scale The scale of the pixel.
 */
void draw_pixel_big(int x, int y, unsigned short color, int scale); 
//--------------------FUNCTION--------------------
/**
 * @brief Draws a character at the given coordinates with the given color and scale.
 * @param x The x-coordinate of the character.
 * @param y The y-coordinate of the character.
 * @param ch The character to draw.
 * @param color The color of the character.
 * @param scale The scale of the character.
 */
void clear_screen(unsigned char *parlcd_mem_base, unsigned short* fb);
//--------------------FUNCTION--------------------
/**
 * @brief Initializes the framebuffer.
 * @param fb The framebuffer.
 */
void init_fb(unsigned short* fb); 
//--------------------FUNCTION--------------------
/**
 * @brief Resets the framebuffer with the given color.
 * @param fb The framebuffer.
 * @param color The color to reset the framebuffer with.
 */
void reset_fb(unsigned short* fb, unsigned short color); 
//--------------------FUNCTION--------------------
/**
 * @brief Clears the screen.
 * @param parlcd_mem_base The memory base for the display.
 * @param fb The framebuffer.
 */
void endgame_clear_screen(unsigned char *parlcd_mem_base); 
//--------------------FUNCTION--------------------
/**
 * @brief Draws a character at the given coordinates with the given color and scale.
 * @param x The x-coordinate of the character.
 * @param y The y-coordinate of the character.
 * @param ch The character to draw.
 * @param color The color of the character.
 * @param scale The scale of the character.
 */
void draw_rectangle(rectangle_t* self);
//--------------------CONSTRUCTOR--------------------
/**
 * @brief Creates a new rectangle.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 */
rectangle_t new_rectangle(int x, int y, int width, int height, unsigned short color);

#endif // __DISPLAY_UTILS_H__