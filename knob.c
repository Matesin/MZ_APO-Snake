
/**
 * @file knob.c
 * @brief This file contains functions for handling the knob.
*/

#include "knob.h"

/**
 * @brief Updates the rotation of the knob.
 * @param self A pointer to the knob.
 * @param mem_base A pointer to the memory base.
 * @return A short value representing the direction of the rotation.
 */

short update_knob_rotation(knob_t *self, unsigned char *mem_base){
    self->prev_value = self->value;
    self->value = (*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o)  >> self->offset) & 0xff;
    short ret = 0;
    if ((self->value < self->prev_value) && abs(self->value - self->prev_value) > MENU_SENSITIVITY){
        ret = -1;   //go back
    } else if ((self->value > self->prev_value) && abs(self->value - self->prev_value) > MENU_SENSITIVITY){
        ret = 1;    //go forward
    }
    return ret;
}

/**
 * @brief Checks if the knob is pressed.
 * @param self A pointer to the knob.
 * @param r The value of the register.
 * @return A boolean value representing if the knob is pressed.
 */

_Bool is_knob_pressed(knob_t *self, int r) {
    if ((r&self->press_reg) != 0) {
        return 1;
    }
    return 0;
}

/**
 * @brief Initializes the knob.
 * @param offset The offset for the specific knob in the register.
 * @param press_reg The value of the register.
 * @param mem_base A pointer to the memory base.
 * @return A knob.
 */

knob_t init_knob(int offset, int press_reg, unsigned char *mem_base) {
    knob_t k;
    k.offset = offset;
    k.value = (*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o) >> k.offset ) & 0xff;
    k.prev_value = k.value;
    k.press_reg = press_reg;
    k.is_pressed = is_knob_pressed;
    k.update_rotation = update_knob_rotation;
    return k;
}