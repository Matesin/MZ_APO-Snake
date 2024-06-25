/**
 * @file led_utils.h
 * @brief This file contains the declarations of functions for handling the LED.
 */

#ifndef __LED_UTILS_H__
#define __LED_UTILS_H__

#include <stdint.h>
#include <unistd.h>
#include "constants.h"
#include "mzapo_regs.h"

/**
 * @brief Lights up a specific LED with a given color.
 * 
 * @param mem_base The memory base for the LED.
 * @param color The color to light up the LED.
 * @param led_num The number of the LED to light up.
 */
void light_up_led(unsigned char* mem_base, unsigned short color, int led_num);

/**
 * @brief Turns off a specific LED.
 * 
 * @param mem_base The memory base for the LED.
 * @param led_num The number of the LED to turn off.
 */
void turn_off_led(unsigned char* mem_base, int led_num);

/**
 * @brief Makes a specific LED flicker with a given color.
 * 
 * @param mem_base The memory base for the LED.
 * @param color The color to make the LED flicker.
 * @param led_num The number of the LED to make flicker.
 */
void flicker_led(unsigned char* mem_base, unsigned short color, int led_num);

/**
 * @brief Updates the LEDs based on the lengths of the snakes.
 * 
 * @param mem_base The memory base for the LED.
 * @param snake1_len The length of the first snake.
 * @param snake2_len The length of the second snake.
 */
void update_led(unsigned char* mem_base, int snake1_len, int snake2_len);

#endif //__LED_UTILS_H__