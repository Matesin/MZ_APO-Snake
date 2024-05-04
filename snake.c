#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
 

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "collisions.h"
#include "menu.h"
#include "buttons.h"
 
unsigned short *fb;

/*
Each snake will be make of array of these squares
int x is each square x coordinate
int y is each square y coordinate
x and y are coordinates of the top let corner of the square
*/
typedef struct {
  int x;
  int y;
} squares;

void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
} 

void draw_char(int x, int y, font_descriptor_t* fdes, char ch) {
}
 
int char_width(font_descriptor_t* fdes, int ch) {
  int width = 0;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    ch -= fdes->firstchar;
    if (!fdes->width) {
      width = fdes->maxwidth;
    } else {
      width = fdes->width[ch];
    }
  }
  return width;
}
 
int main(int argc, char *argv[]) {  
  
  font_descriptor_t* fdes = &font_winFreeSystem8x16;
  int snake_length = 3;
  int square_size = 15;

  squares snake[snake_length];
  // initialized snake coords
  for (int k = 0; k < snake_length; k++) {
    snake[k].x = 150 - square_size;
    snake[k].y = 150;
  }

  unsigned char *parlcd_mem_base, *mem_base;
  int i,j;
  int ptr;
  unsigned int c;
  fb  = (unsigned short *)malloc(320*480*2);
 
  printf("Starting program\n");
 
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL)
    exit(1);
 
  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
 
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  ptr=0;
  // remove background, initialize on 0
  for (i = 0; i < 320 ; i++) {
    for (j = 0; j < 480 ; j++) {
      c = 0;
      fb[ptr]=c;
      parlcd_write_data(parlcd_mem_base, fb[ptr++]);
    }
  }
 
  struct timespec loop_delay;
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 150 * 1000 * 1000;
  int xx=0, yy=0;
  int p = 0, q = 0;
  
  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

  int curr_green = (((r>>8)&0xff));
  int prev_green = (((r>>8)&0xff));
  int menu_button = 1;
  show_menu();
  bool menu_running = true;

  // Menu loop
  while (menu_running) {
  
    show_menu();

    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    curr_green = (((r>>8)&0xff)); // green knob

    menu_button = modify_while_rotating(curr_green, prev_green, menu_button, 3);

    if (menu_button == 1) {
      draw_outher_button(140, 30, 340, 100);
    } else if (menu_button == 2) {
      draw_outher_button(140, 130, 340, 200);
    } else if (menu_button == 3) {
      draw_outher_button(140, 230, 340, 300);
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < 480*320 ; ptr++) {
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }

    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);

    for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u;
    } 

  // If green knob pressed
    if ((r&0x7000000)!=0) {
      switch(menu_button) {
        case 1:
          menu_running = false;
          break;
        case 2:
          break;
        case 3:
          break;
      }
    }
    prev_green = curr_green;
  }

/*
GAME LOOP
*********************************************************************************************************************************
*/

/*
  Snake's direction
  1 means LEFT, 2 means TOP, 3 means RIGHT, 4 means DOWN
*/
int snake_direction = 1;

int curr_snake_dir = ((r&0xff));
int prev_snake_dir = ((r&0xff));

  while (1) {
    squares old_head = snake[0];
 
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    // button pressed
    if ((r&0x7000000)!=0) {
      printf("k\n");
    }

    // moving head
    switch(snake_direction) {
      case 1: 
        snake[0].x -= square_size;
        break;
      case 2:
        snake[0].y -= square_size;
        break;
      case 3:
        snake[0].x += square_size;
        break;
      case 4:
        snake[0].y += square_size;
        break;
    }
    
    curr_snake_dir = ((r&0xff)); // blue knob

    snake_direction = modify_while_rotating(curr_snake_dir, prev_snake_dir, snake_direction, 4);

    prev_snake_dir = curr_snake_dir;
    
    // yy = (((r>>16)&0xff)*320)/256; // green knob

    // moving tail
      for (int k = 1; k < snake_length; k++) {
        squares temp = snake[k]; // saving tail square into temp
        // setting tail squares to be old head square
        snake[k].x = old_head.x; 
        snake[k].y = old_head.y;

        // saved tail temp is a "new" old head for the tail square behind him
        old_head = temp; 
    }

 
    for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u; 
    }
    
    // draw square
    for (int k = 0; k < snake_length; k++) {
      for (j=0; j<square_size; j++) {
        for (i=0; i<square_size; i++) {
            draw_pixel(i+snake[k].x,j+snake[k].y,0x7ff);
        }
      }
    }

    if (!check_collisions(snake[0].x, snake[0].y)) {
      printf("Snake out\n");
      break;
    }


 
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < 480*320 ; ptr++) {
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
 
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }

/*
*********************************************************************************************************************************
*/
 
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
    parlcd_write_data(parlcd_mem_base, 0);
  }
 
  printf("Goodbye world\n");
 
  return 0;
}
