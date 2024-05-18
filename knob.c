#include "knob.h"

short update_knob_rotation(knob_t *self, unsigned char *mem_base){
    self->prev_value = self->value;
    self->value = (*(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o)  >> self->offset) & 0xff;
    short ret = 0;
    if ((self->value < self->prev_value) && abs(self->value - self->prev_value) > MENU_SENSITIVITY){
        printf("moving down\n");
        ret = -1;    //todo change to -1 for direction
    } else if ((self->value > self->prev_value) && abs(self->value - self->prev_value) > MENU_SENSITIVITY){
        printf("moving up\n");
        ret = 1;
    }
    return ret;
}

_Bool is_knob_pressed(knob_t *self, int r) {
    if ((r&self->press_reg) != 0) {
        return 1;
    }
    return 0;
}


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