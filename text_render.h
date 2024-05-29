/**
 * @file text_render.h
 * @brief This file contains the declarations of functions and structures for rendering text.
 
*/

#ifndef __TEXT_RENDER_H__
#define __TEXT_RENDER_H__
#include "font_types.h"
#include "constants.h"
#include <stdint.h>
#include <stdio.h>
//--------------------STRUCTURE--------------------
/**
 * @brief A structure representing a text.
 */
typedef struct text{
    char* text;
    int scale;
    int start_x;
    int start_y;
    unsigned short color;
    void (*draw)(struct text* self);
} text_t;
//--------------------FUNCTION--------------------
/**
 * @brief Draws a character.
 * @param x The x-coordinate of the character.
 * @param y The y-coordinate of the character.
 * @param ch The character to draw.
 * @param color The color of the character.
 * @param scale The scale of the character.
*/
void draw_char(int x, int y, char ch, unsigned short color, int scale);
//--------------------FUNCTION--------------------
/**
 * @brief Draws a text line.
 * @param x The x-coordinate of the text.
 * @param y The y-coordinate of the text.
 * @param text The text to draw.
 * @param color The color of the text.
 * @param scale The scale of the text.
*/
void draw_text_line(int x, int y, char* text, unsigned short color, int scale);
//--------------------FUNCTION--------------------
/**
 * @brief Draws a text.
 * @param self A pointer to the text.
*/
int char_width(int ch);
//--------------------FUNCTION--------------------
/**
 * @brief Measures the width of a text.
 * @param text The text to measure.
 * @param scale The scale of the text.
*/
short measure_text_width(char* text, int scale);
//--------------------CONSTRUCTOR-----------------
/**
 * @brief Creates a new text.
 * @param x The x-coordinate of the text.
 * @param y The y-coordinate of the text.
 * @param text The text to draw.
 * @param color The color of the text.
 * @param scale The scale of the text.
*/
text_t new_text(int x, int y, char* text, unsigned short color, int scale);

#endif // __TEXT_RENDER_H__
