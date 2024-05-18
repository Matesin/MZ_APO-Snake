#ifndef __KNOB_H__
#define __KNOB_H__
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "constants.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct knob{
    int value;
    int prev_value;
    int offset; // offset for the specific knob in the register
    int press_reg;
    short (*update_rotation) (struct knob *self, unsigned char *mem_base);
    _Bool (*is_pressed) (struct knob *self, int r);
} knob_t;

short update_knob_rotation(knob_t *self, unsigned char *mem_base);
_Bool is_knob_pressed(knob_t *self, int r);
knob_t init_knob(int offset, int press_reg, unsigned char *mem_base);

#endif //__KNOB_H__
