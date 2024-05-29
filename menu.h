/**
 * @file menu.h
 * @brief This file contains the declarations of functions and structures for handling the menu.
 */

#ifndef __MENU__
#define __MENU__
#include <stdlib.h>
#include "display_utils.h"
#include "text_render.h"
#include "constants.h"
#include "knob.h"

//--------------------STRUCTURE--------------------
/**
 * @brief A structure representing a button.
 */

typedef struct button{
    _Bool selected;
    rectangle_t rectangle;
    text_t text;
    unsigned short cur_color;
    unsigned short base_color;
    unsigned short selected_color;
    void (*draw) (struct button* self);
} button_t;

//--------------------STRUCTURE--------------------
/**
 * @brief A structure representing a menu.
 */
typedef struct menu{
    int padding; ///< The padding for the menu.
    text_t title; ///< The title of the menu.
    unsigned short button_base_color; ///< The base color of the buttons in the menu.
    unsigned short button_selected_color; ///< The color of the selected button in the menu.
    unsigned short button_text_color; ///< The color of the text in the buttons of the menu.
    button_t *buttons; ///< The buttons in the menu.
    knob_t* controlling_knob; ///< The knob controlling the menu.
    short num_buttons; ///< The number of buttons in the menu.
    short selected_button; ///< The currently selected button in the menu.
    void (*show) (struct menu* self); ///< A function pointer to show the menu.
    void (*update) (struct menu* self, short selected_button); ///< A function pointer to update the menu.
} menu_t;
//--------------------FUNCTION--------------------
/**
 * @brief Draws a button.
 * @param self A pointer to the button.
*/
void draw_button(button_t* self); 
//--------------------FUNCTION--------------------
/**
 * @brief Draws the menu.
 * @param self A pointer to the menu.
*/

void draw_menu(menu_t* self); 
//--------------------FUNCTION--------------------
/**
 * @brief Updates the menu.
 * @param self A pointer to the menu.
 * @param selected_button The currently selected button.
*/
void update_menu(menu_t* self, short selected_button); 
//--------------------FUNCTION--------------------
/**
 * @brief Counts number of elements in an array.
 * @param arr The array.
 * @return The number of elements in the array.
*/
int arr_num_elements(char** arr); 
//--------------------CONSTRUCTOR--------------------
/**
 * @brief Initializes a button.
 * @param text The text of the button.
 * @param selected A boolean value representing if the button is selected.
 * @param x_coord The x-coordinate of the button.
 * @param y_coord The y-coordinate of the button.
 * @param base_color The base color of the button.
 * @param selected_color The color of the selected button.
 * @param text_color The color of the text in the button.
 * @param button_width The width of the button.
 * @param button_height The height of the button.
 * @return A button.
*/

button_t new_button(char* text, _Bool selected, int x_coord, int y_coord, unsigned short base_color, unsigned short selected_color, unsigned short text_color, short button_width, short button_height); 
//--------------------CONSTRUCTOR--------------------
/**
 * @brief Initializes the menu.
 * @param title The title of the menu.
 * @param title_color The color of the title.
 * @param button_base_color The base color of the buttons in the menu.
 * @param button_selected_color The color of the selected button in the menu.
 * @param button_text_color The color of the text in the buttons of the menu.
 * @param button_texts The texts of the buttons in the menu.
 * @param num_buttons The number of buttons in the menu.
 * @return A menu.
*/
menu_t new_menu(char* title, unsigned short title_color, unsigned short button_base_color, unsigned short button_selected_color, unsigned short button_text_color, char** button_texts, short num_buttons); 

#endif // __MENU_H__