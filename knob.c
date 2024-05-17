#include "knob.h"
#include <stdint.h>
void update_knob_rotation(knob_t *self, unsigned char *mem_base){
    self->prev_value = self->value;
    self->value = (*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o)  >> self->offset) & 0xff;
}

knob_t init_knob(int offset, int press_reg, unsigned char *mem_base) {
    knob_t k;
    k.offset = offset;
    k.value = (*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o) >> k.offset ) & 0xff;
    k.prev_value = k.value;
    k.press_reg = press_reg;
    k.update_rotation = update_knob_rotation;
    return k;
}