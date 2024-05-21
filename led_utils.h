#ifndef __LED_UTILS_H__
#define __LED_UTILS_H__


#include <stdint.h>
#include <unistd.h>
#include "constants.h"
#include "mzapo_regs.h"


void light_up_led(unsigned char* mem_base, unsigned short color, int led_num);
void turn_off_led(unsigned char* mem_base, int led_num);
void flicker_led(unsigned char* mem_base, unsigned short color, int led_num);

#endif //__LED_UTILS_H__