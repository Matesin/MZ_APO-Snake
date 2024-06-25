/**
 * @file constants.h
 * @brief This file contains definitions for various constants used in the game.
 */

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define COLOR uint16_t ///< Defines a type for color.
#define BOOL uint8_t ///< Defines a type for boolean.

/**
 * @brief Macro to convert RGB values to a 16-bit color.
 */
#define RGB(r, g, b) ((COLOR) (((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F))

/**
 * @brief Macro to extract the red component from a 16-bit color.
 */
#define RED(c) (((r) >> 11) & 0x1F)

/**
 * @brief Macro to extract the green component from a 16-bit color.
 */
#define GREEN(c) (((r) >> 5) & 0x3F)

/**
 * @brief Macro to extract the blue component from a 16-bit color.
 */
#define BLUE(c) (((r) >> 0) & 0x1F)

// Error codes
#define NO_ERROR 0 ///< Represents no error.
#define ERR_NO_MEM 1 ///< Represents an error due to no memory.
#define ERR_INVALID_ARGUMENT 2 ///< Represents an error due to an invalid argument.
#define ERR_REINIT 3 ///< Represents an error due to reinitialization.

// LCD properties
#define LCD_WIDTH 480 ///< The width of the LCD.
#define LCD_HEIGHT 320 ///< The height of the LCD.
#define LCD_SIZE LCD_WIDTH * LCD_HEIGHT ///< The size of the LCD.
#define FRAMEBUFFER_IDX(x, y) ((y) * LCD_WIDTH + (x)) ///< Macro to calculate the index in the framebuffer.

// Menu properties
#define MENU_TEXT_SIZE 4 ///< The size of the menu text.
#define MENU_Y_PADDING 20 ///< The vertical padding in the menu.
#define MENU_X_PADDING 50 ///< The horizontal padding in the menu.

// Button properties
#define BUTTON_WIDTH 200 ///< The width of a button.
#define BUTTON_HEIGHT 80 ///< The height of a button.
#define BUTTON_TEXT_X_OFFSET 20 ///< The horizontal offset for the button text.
#define BUTTON_TEXT_Y_OFFSET 10 ///< The vertical offset for the button text.
#define BUTTON_TEXT_SIZE 4 ///< The size of the button text.

// Player properties
#define PLAYER_SPEED 2 ///< The speed of the player.

// Game properties
#define SNAKE_SQUARE_SIZE 20 ///< The size of a snake square.
#define SNAKE_START_LEN 3 ///< The starting length of the snake.
#define SNAKE_MAX_LEN 50 ///< The maximum length of the snake.
#define SNAKE_FOOD_SIZE 10 ///< The size of the snake food.

//TEXT PROPERTIES
#define BLOCK_SIZE 20 ///< The size of a block.

//KNOB PROPERTIES
#define MENU_SENSITIVITY 2 ///< The sensitivity of the menu knob.
#define GAME_SENSITIVITY 2 ///< The sensitivity of the game knob.

//SCORE DISPLAY PROPERTIES
#define SCORE_TEXT_SIZE 2 ///< The size of the score text.

//LED PROPERTIES

//16 LEDs, used %17
#define LED_RESET 17 ///< The reset value for the LEDs.

enum Boolean {FALSE, TRUE};

enum Direction{
  UP,
  RIGHT,
  DOWN,
  LEFT,
};


#endif //__CONSTANTS_H__