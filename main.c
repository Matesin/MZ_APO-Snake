/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON

  change_me.c      - main file

  include your name there and license for distribution.

  Remove next text: This line should not appear in submitted
  work and project name should be change to match real application.
  If this text is there I want 10 points subtracted from final
  evaluation.

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"

#define COLOR uint16_t
#define BOOL uint8_t

#define RGB(r, g, b) ((COLOR) (((r) & 0x1F) << 11) | (((g) & 0x3F) << 5) | ((b) & 0x1F))
#define RED(c) (((r) >> 11) & 0x1F)
#define GREEN(c) (((r) >> 5) & 0x3F)
#define BLUE(c) (((r) >> 0) & 0x1F)
 
#define NO_ERROR 0
#define ERR_NO_MEM 1
#define ERR_INVALID_ARGUMENT 2
#define ERR_REINIT 3
 
#define LCD_WIDTH 480
#define LCD_HEIGHT 320
#define FRAMEBUFFER_IDX(x, y) ((y) * LCD_WIDTH + (x))

typedef struct display_t {
  COLOR *frameBuffer = 0;
  unsigned char* parlcd_mem_base;
  uint16_t width;
  uint16_t height;
 
  BOOL (*drawPixel)(struct display_t *display, uint16_t x, uint16_t y);
  BOOL (*drawDisplay)(struct display_t *display);
} display_t;
 
BOOL drawPixel(struct display_t *display, uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue){
  display[FRAMEBUFFER_IDX(x, y)] = RGB(red, green, blue);
  return NO_ERROR;
}
 
BOOL drawDisplay(struct display_t *display){
  parlcd_write_cmd(display->parlcd_mem_base, 0x2c);
  for (uint16_t y = 0; y < display->height; y++){
    for (uint16_t x = 0; x < display->width; x++){   
      parlcd_write_data(display->parlcd_mem_base, fb[ptr++]);
    }
  }
}
 
BOOL display_init(display_t* display, unsigned char* parlcd_mem_base){
  if (display == NULL){
    return ERR_INVALID_ARGUMENT;
  } else if (display->frameBuffer != NULL) {
    return ERR_REINIT;
  }
 
  parlcd_hx8357_init(parlcd_mem_base);
 
  display->parlcd_mem_base = parlcd_mem_base;
  display->width = LCD_WIDTH;
  display->height = LCD_HEIGHT; 
  display->drawPixel = drawPixel;
  display->drawDisplay = drawDisplay;
 
  display->frameBuffer = (COLOR*) calloc(LCD_HEIGHT * LCD_WIDTH, 3);
 
  if (display->frameBuffer == NULL){
    return ERR_NO_MEM;
  }
  return NO_ERROR;
}
//code for inspo initially included in main
  // unsigned char *parlcd_mem_base, *mem_base;
  // int i,j;
  // int ptr;
  // unsigned int c;
  // display_t display;
 
  // printf("Hello world\n");
 
  // parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  // if (parlcd_mem_base == NULL)
  //   exit(1);
 
  // mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  // if (mem_base == NULL)
  //   exit(1);
 
  // display_init(&display, parlcd_mem_base);
 
  // parlcd_write_cmd(parlcd_mem_base, 0x2c);
  // ptr=0;
  // for (i = 0; i < 320 ; i++) {
  //   for (j = 0; j < 480 ; j++) {
  //     c = 0;
  //     fb[ptr]=c;
  //     parlcd_write_data(parlcd_mem_base, fb[ptr++]);
  //   }
  // }
 
  // struct timespec loop_delay;
  // loop_delay.tv_sec = 0;
  // loop_delay.tv_nsec = 150 * 1000 * 1000;
  // int xx=0, yy=0;
  // while (1) {
 
  //   int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  //   if ((r&0x7000000)!=0) {
  //     break;
  //   }
  //   xx = ((r&0xff)*480)/256;
  //   yy = (((r>>8)&0xff)*320)/256;
 
  //   for (ptr = 0; ptr < 320*480 ; ptr++) {
  //       fb[ptr]=0u;
  //   }
  //   for (j=0; j<60; j++) {
  //     for (i=0; i<60; i++) {
  //       draw_pixel(i+xx,j+yy,0x7ff);
  //     }
  //   }
 
  //   parlcd_write_cmd(parlcd_mem_base, 0x2c);
  //   for (ptr = 0; ptr < 480*320 ; ptr++) {
  //       parlcd_write_data(parlcd_mem_base, fb[ptr]);
  //   }
 
  //   clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  // }
 
  // parlcd_write_cmd(parlcd_mem_base, 0x2c);
  // for (ptr = 0; ptr < 480*320 ; ptr++) {
  //   parlcd_write_data(parlcd_mem_base, 0);
  // }
 
  // printf("Goodbye world\n");
 
  // return 0;

int main(int argc, char *argv[])
{

  /* Serialize execution of applications */

  /* Try to acquire lock the first */
  if (serialize_lock(1) <= 0) {
    printf("System is occupied\n");

    if (1) {
      printf("Waitting\n");
      /* Wait till application holding lock releases it or exits */
      serialize_lock(0);
    }
  }
  printf("Hallo Welt!\n");
  sleep(2);
  printf("Auf Wiedersehen!\n");


  /* Release the lock */
  serialize_unlock();

  return 0;
}
