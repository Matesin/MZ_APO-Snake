#ifndef __DISPLAY_UTILS_H__
#define __DISPLAY_UTILS_H__
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"
#include "constants.h"
#include "mzapo_parlcd.h"

extern font_descriptor_t* fdes;
extern unsigned short* fb;
unsigned char* init_mem_base();
unsigned char* init_parlcd_mem_base();
void draw_pixel(int x, int y, unsigned short color);
void draw_pixel_big(int x, int y, unsigned short color, int scale);
void clear_screen(unsigned char *parlcd_mem_base, unsigned short* fb);
void init_fb(unsigned short* fb);
void endgame_clear_screen(unsigned char *parlcd_mem_base);

#endif // __DISPLAY_UTILS_H__