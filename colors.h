#ifndef __COLORS_H__
#define __COLORS_H__
/*define basic colors, rest can be added when needed
* 16-bit color format 0b(RRRRR)(GGGGGG)(BBBBB)
*/
enum Colors{
    WHITE = 0xffff,
    BLACK = 0x0000,
    RED = 0xf800,
    GREEN = 0x07E0,
    BLUE = 0x001f,
    LIGHT_GREEN = 0xa734,
    SUPER_LIGHT_GREEN = 0xc6f9,
    DARK_GREEN = 0x3509,
    CYAN = 0x4d96
};

enum Menu_colors {
    MENU_BACKGROUND_COLOR = SUPER_LIGHT_GREEN,
    MENU_BUTTON_COLOR = LIGHT_GREEN,
    MENU_PICKED_BUTTON_COLOR = DARK_GREEN
};

enum Game_colors {
    GAME_BACKGROUND_COLOR = BLACK
};

#endif //__COLORS_H_