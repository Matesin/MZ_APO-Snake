#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__
#define COLOR uint16_t
#define BOOL uint8_t

#define RGB(r, g, b) ((COLOR) (((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F))
#define RED(c) (((r) >> 11) & 0x1F)
#define GREEN(c) (((r) >> 5) & 0x3F)
#define BLUE(c) (((r) >> 0) & 0x1F)
 
#define NO_ERROR 0
#define ERR_NO_MEM 1
#define ERR_INVALID_ARGUMENT 2
#define ERR_REINIT 3
 
#define LCD_WIDTH 480
#define LCD_HEIGHT 320
#define LCD_SIZE LCD_WIDTH * LCD_HEIGHT
#define FRAMEBUFFER_IDX(x, y) ((y) * LCD_WIDTH + (x))

//MENU PROPERTIES
#define MENU_TEXT_SIZE 4
#define MENU_Y_PADDING 20
#define MENU_X_PADDING 50

//BUTTON PROPERTIES
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80
#define BUTTON_TEXT_X_OFFSET 20
#define BUTTON_TEXT_Y_OFFSET 10
#define BUTTON_TEXT_SIZE 4


//PLAYER PROPERTIES
#define PLAYER_SPEED 2

//TEXT PROPERTIES
#define BLOCK_SIZE 20

//KNOB PROPERTIES
#define MENU_SENSITIVITY 3
#define GAME_SENSITIVITY 2

//LED PROPERTIES
#define LED_RESET 17    //16 led's, used %17

enum Boolean {FALSE, TRUE};

#endif // __CONSTANTS_H__