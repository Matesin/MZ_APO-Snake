
#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "serialize_lock.h"
#include "font_types.h"
#include "font_prop14x16.c"
#include "display_utils.h"
#include "colors.h"
#include "snake.h"
#include "knob.h"
#include "snake_food.h"
#include "text_render.h"

font_descriptor_t* fdes = &font_winFreeSystem14x16;

void play_game(unsigned char *parlcd_mem_base, unsigned char* mem_base);
void draw_pixel(int x, int y, unsigned short color);
void draw_char(int x, int y, char ch, unsigned short color, int scale);
void draw_pixel_big(int x, int y, unsigned short color, int scale);
int char_width(int ch);
void endgame_clear_screen(unsigned char *parlcd_mem_base);
void clear_screen(unsigned char *parlcd_mem_base, unsigned short* fb);
void init_fb(unsigned short* fb);


//Initialize display
unsigned short *fb;

unsigned char *parlcd_mem_base;
unsigned char *mem_base;
int scale=4;
struct timespec loop_delay;


int main(void){
  //Initialize framebuffer
  int ptr = 0;
  fb = (unsigned short *)malloc(320*480*2);
  //Initialize peripherals
  mem_base = init_mem_base();
  parlcd_mem_base = init_parlcd_mem_base();
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 150 * 1000 * 5000;

  int x_offset = 150;
  int y_offset = 0; //todo change to center of the screen
  short update_value;
  char text3[5] = "PLAY";
  char text4[5] = "QUIT";
  short num_buttons = 2;
  char arrow2[3] = "->";
  //TODO: change BLOCK_SIZE to something that actually makes sense
  text_t menu_start_game = new_text(x_offset, 0, text3, WHITE, scale);
  text_t menu_quit = new_text(x_offset, 60, text4, WHITE, scale);
  text_t menu_arrow = new_text(BLOCK_SIZE, 0, arrow2, BLUE, scale); //change space between chars
  knob_t green_knob = init_knob(8, 0x2000000, mem_base); //initialize green knob
  //TODO: Implement menu, decompose to functions
  printf("Hello mf\n");

  while(1) {
    
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    update_value = green_knob.update_rotation(&green_knob, mem_base);
    y_offset =  update_value != 0 ? abs(y_offset + update_value) % num_buttons : y_offset;
    printf("Y: %d\n", y_offset);
    // if(green_knob.prev_value != green_knob.value) { //for arrow impl...
    //   y_offset = y_offset == 0 ? 1 : 0;
    // }

    menu_arrow.start_y = 50 * y_offset;
    //draw menu text
    reset_fb(fb);
    menu_start_game.draw(&menu_start_game);
    menu_quit.draw(&menu_quit);
    menu_arrow.draw(&menu_arrow);

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }

    if (green_knob.is_pressed(&green_knob, r)) { //if green button is pressed
      if (y_offset == 0) { //if game button is picked
        play_game(parlcd_mem_base, mem_base);
      } else {
        break;
      }
    }

    // clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
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
void play_game(unsigned char *parlcd_mem_base, unsigned char *mem_base){
  //TODO: ADD MACROS INSTEAD OF MAGIC NUMBERS
  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 150 * 1000 * 1000; 
  snake_t snake = init_snake(BLUE, RIGHT);
  knob_t red_knob = init_knob(16, 0x4000000, mem_base);
  knob_t green_knob = init_knob(8, 0x2000000, mem_base);
  knob_t blue_knob = init_knob(0, 0x1000000, mem_base);
  snake_food_t food = init_food(WHITE);

  reset_fb(fb);
  snake.draw(&snake, parlcd_mem_base);

  while(1) {
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    if (red_knob.is_pressed(&red_knob, r)) {
      clear_screen(parlcd_mem_base, fb);
      exit(0);
    }

    //UPDATE SNAKE
    green_knob.update_rotation(&green_knob, mem_base);
    snake.update(&snake, &green_knob);
    
    snake.draw(&snake, parlcd_mem_base);
    food.draw(&food, parlcd_mem_base);
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    clear_screen(parlcd_mem_base, fb);
    reset_fb(fb);
  }
}
