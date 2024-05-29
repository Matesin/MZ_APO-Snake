/**
 * @file colors.h
 * @brief This file contains definitions for various colors used in the game.
 */

#ifndef __COLORS_H__
#define __COLORS_H__

/**
 * @brief Enum representing basic colors in 16-bit format 0b(RRRRR)(GGGGGG)(BBBBB).
 */
enum Colors{
    WHITE = 0xffff, ///< Represents the color white.
    BLACK = 0x0000, ///< Represents the color black.
    RED = 0xf800, ///< Represents the color red.
    GREEN = 0x07E0, ///< Represents the color green.
    BLUE = 0x001f, ///< Represents the color blue.
    SUPER_LIGHT_BLUE = 0xbfbf, ///< Represents a super light shade of blue.
    LIGHT_GREEN = 0xa734, ///< Represents a light shade of green.
    SUPER_LIGHT_GREEN = 0xc6f9, ///< Represents a super light shade of green.
    DARK_GREEN = 0x3509, ///< Represents a dark shade of green.
    CYAN = 0x4d96, ///< Represents the color cyan.
    JOZIN_Z_BAZIN = 0xAE51 ///< Represents a custom color.
};

/**
 * @brief Enum representing colors used in the menu.
 */
enum Menu_colors {
    MENU_BACKGROUND_COLOR = JOZIN_Z_BAZIN, ///< Represents the background color of the menu.
    MENU_BUTTON_COLOR = LIGHT_GREEN, ///< Represents the color of the menu buttons.
    MENU_PICKED_BUTTON_COLOR = DARK_GREEN ///< Represents the color of the selected menu button.
};

/**
 * @brief Enum representing colors used in the game.
 */
enum Game_colors {
    GAME_BACKGROUND_COLOR = SUPER_LIGHT_GREEN ///< Represents the background color of the game.
};

#endif //__COLORS_H_