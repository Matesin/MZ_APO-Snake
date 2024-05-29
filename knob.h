/**
 * @file knob.h
 * @brief This file contains the declarations of functions and structures for handling the knob.
 */

#ifndef __KNOB_H__
#define __KNOB_H__

#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "constants.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//--------------------STRUCTURE--------------------
/**
 * @brief A structure representing a knob.
 */
typedef struct knob{
    int value; ///< The current value of the knob.
    int prev_value; ///< The previous value of the knob.
    int offset; ///< The offset for the specific knob in the register.
    int press_reg; ///< The register for the press action of the knob.
    short (*update_rotation) (struct knob *self, unsigned char *mem_base); ///< A function pointer to update the rotation of the knob.
    _Bool (*is_pressed) (struct knob *self, int r); ///< A function pointer to check if the knob is pressed.
} knob_t;
//--------------------FUNCTION--------------------
/**
 * @brief Updates the rotation of the knob.
 * @param self A pointer to the knob.
 * @param mem_base A pointer to the memory base.
 * @return A short value representing the direction of the rotation.
 */
short update_knob_rotation(knob_t *self, unsigned char *mem_base);
//--------------------FUNCTION--------------------
/**
 * @brief Checks if the knob is pressed.
 * @param self A pointer to the knob.
 * @param r The value of the register.
 * @return A boolean value representing if the knob is pressed.
 */
_Bool is_knob_pressed(knob_t *self, int r);
//--------------------CONSTRUCTOR--------------------
/**
 * @brief Initializes the knob.
 * @param offset The offset for the specific knob in the register.
 * @param press_reg The value of the register.
 * @param mem_base A pointer to the memory base.
 * @return A knob.
 */
knob_t init_knob(int offset, int press_reg, unsigned char *mem_base); 

#endif // __KNOB_H__