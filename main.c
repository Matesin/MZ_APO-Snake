
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
#include "font_types.h"
// #include "game.h"
// #include "game_graphics.h"
#include "constants.h"
#include "display_utils.h"
#include "font_prop14x16.c"
enum Direction{
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

enum Colors{
  RED = 0xF800,
  WHITE = 0xffff,
  BLACK = 0x0000,
  BLUE = 0x001f,
};
 
/*
PLACE IN SNAKE.H
*/
typedef struct snake_square{
  //top left pixel of the square
  int x_coord;
  int y_coord;
} snake_sq_t;

typedef struct snake {
  snake_sq_t* squares;
  int speed;
  char direction;
  int length;
  int color;
  void (*update)(struct snake *self, int knob_val);
  void (*draw)(struct snake *self, unsigned char* parlcd_mem_base);
} snake_t;

typedef struct {
    int value;
    int prev_value;
    int offset; // offset for the specific knob in the register
    int press_reg;
} knob_t;

/*
END PLACE IN SNAKE.H
*/

font_descriptor_t* fdes = &font_winFreeSystem14x16;
void play_game(unsigned char *parlcd_mem_base);
void draw_pixel(int x, int y, unsigned short color);
void draw_char(int x, int y, char ch, unsigned short color, int scale);
void draw_pixel_big(int x, int y, unsigned short color, int scale);
int char_width(int ch);
void endgame_clear_screen(unsigned char *parlcd_mem_base);
void clear_screen(unsigned char *parlcd_mem_base, unsigned short* fb);
void init_fb(unsigned short* fb);
//place in snake.h
void draw_snake(snake_t *self, unsigned char *parlcd_mem_base);

knob_t init_knob(int r, int offset, int press_reg);
void update_knob(knob_t* k, int r);



//Initialize display
unsigned short *fb;
unsigned char *parlcd_mem_base;
unsigned char *mem_base;
int scale=4;
struct timespec loop_delay;


int main(void){
  //Initialize framebuffer
  int i;
  int ptr;
  fb  = (unsigned short *)malloc(320*480*2);

  //Initialize peripherals
  mem_base = init_mem_base();
  parlcd_mem_base = init_parlcd_mem_base();
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  ptr=0;
  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 150 * 1000 * 1000;

  printf("Hello world\n");
  int x_offset = 150;
  int y_offset = 0; //todo change to center of the screen
  char text1[] = {'P', 'L', 'A', 'Y'};
  char text2[] = {'Q', 'U', 'I', 'T'};
  char arrow[] = {'-','>'};
  int BLOCK_SIZE = 20; //tmp
  
  knob_t green_knob = init_knob(r, 8, 0x2000000);
  int green_button = (r>>8)&0xff;
  int prev_green_button = green_button;


  while(1) {
    
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    prev_green_button = green_button;
    green_button = (r>>8)&0xff;
    // update_knob(&green_knob, r);
    // green_knob.prev_value = green_knob.value;
    // green_knob.value = (*(mem_base + SPILED_REG_KNOBS_8BIT_o) >> green_knob.offset ) & 0xff;
    


    if(green_button != prev_green_button) { //for arrow impl...
      printf("updated\n");
      y_offset = y_offset == 0 ? 1 : 0;
    }

    //draw menu
    for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u;
    }
    for (i = 0; i < 4; i++) {
      draw_char(x_offset + i * 2 * BLOCK_SIZE, 0, text1[i], 0xffff, scale);
      if (i == 3) {
        draw_char(x_offset + i * 32, 60, text2[i], 0xffff, scale);
      } else {  //font optimization
        draw_char(x_offset + i * 2 * BLOCK_SIZE, 60, text2[i], 0xffff, scale);
      }
    }

    //draw arrow
    for (int i = 0; i < 2; i++){
        if (y_offset == 0) {
        draw_char(BLOCK_SIZE, y_offset, arrow[i], 0xF800, scale);
      } else {
        draw_char(BLOCK_SIZE, 50, arrow[i], 0xF800, scale);
      }
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }

    if ((r&0x2000000)!=0) { //if green button is pressed
      if (y_offset == 0) { //if game button is picked
       for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u;
        }
        play_game(parlcd_mem_base);
      } else {
        break;
      }
    }
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    //clear screen for new frame
    clear_screen(parlcd_mem_base, fb);
  }
  printf("ended game, clearing screeen, bye bye mf\n");
  endgame_clear_screen(parlcd_mem_base);
  return 0;
}
/*****************************************************************************
 * GAME LOOP
******************************************************************************/
void play_game(unsigned char *parlcd_mem_base){
  //TODO: ADD MACROS INSTEAD OF MAGIC NUMBERS
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 150 * 1000 * 5000; 
  int snake_max_len = 50;
  snake_t snake;
  snake.squares = (snake_sq_t*) malloc(snake_max_len * sizeof(snake_sq_t)); //fuck dynamic allocation, it's too expensive
  snake.direction = RIGHT;
  snake.speed = 25; //snake speed square size by default
  snake.length = 3; //init length 
  snake.color = BLUE;
  snake.draw = draw_snake;
  int ptr = 0;

  // knob_t green_knob = init_knob(mem_base, 16, 0x4000000);
  // knob_t blue_knob = init_knob(mem_base, 0, 0x1000000);

  for (int i = 0; i < snake.length; i++) {
    snake.squares[i].x_coord = 150 - snake.speed * i;  //25 -> square size
    snake.squares[i].y_coord = 150;
  }
  printf("snake initialized\n");

  while(1) {
    init_fb(fb);
    snake.draw(&snake, parlcd_mem_base);
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
      for (ptr = 0; ptr < LCD_SIZE; ptr++){
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
  }
}

void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}

void draw_char(int x, int y, char ch, unsigned short color, int scale) {
  int w = char_width(ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth+15)/16;
      ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
    }
    int i, j;
    for (i=0; i<fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big(x+scale*j, y+scale*i, color, scale);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

int char_width(int ch) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch-fdes->firstchar];
  }
  return width;
}

void draw_pixel_big(int x, int y, unsigned short color, int scale) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel(x+i, y+j, color);
    }
  }
}

void clear_screen(unsigned char *parlcd_mem_base, unsigned short* fb){
  int ptr = 0;
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
  }
}

void init_fb(unsigned short* fb){
  int ptr = 0;
  for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u;
  }
}

void endgame_clear_screen(unsigned char *parlcd_mem_base){
  int ptr;
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
    parlcd_write_data(parlcd_mem_base, 0);
  }
}

void draw_snake(snake_t *self, unsigned char *parlcd_mem_base){
  int ptr = 0;
  for (int i = 0; i < self->length; i++) {
      draw_pixel_big(self->squares[i].x_coord, self->squares[i].y_coord, self->color, self->speed);
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
}

knob_t init_knob(int offset, int press_reg, int r) {
    knob_t k;
    k.offset = offset;
    k.value = (r >> k.offset ) & 0xff;
    k.prev_value = k.value;
    k.press_reg = press_reg;
    return k;
}

void update_knob(knob_t* k, int r) {
    k->prev_value = k->value;
    k->value = (r >> k->offset) & 0xff;
}
