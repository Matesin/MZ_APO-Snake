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
#define FRAMEBUFFER_IDX(x, y) ((y) * LCD_WIDTH + (x))

#endif // __CONSTANTS_H__