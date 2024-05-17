#ifndef __KNOB_H__
#define __KNOB_H__
#include "mzapo_phys.h"
#include "mzapo_regs.h"

typedef struct knob{
    int value;
    int prev_value;
    int offset; // offset for the specific knob in the register
    int press_reg;
    void (*update_rotation) (struct knob *self, unsigned char *mem_base);
} knob_t;

void update_knob_rotation(knob_t *self, unsigned char *mem_base);
knob_t init_knob(int offset, int press_reg, unsigned char *mem_base);

#endif //__KNOB_H__
