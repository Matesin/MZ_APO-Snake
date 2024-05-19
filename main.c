
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
#include "menu.h"


font_descriptor_t* fdes = &font_winFreeSystem14x16;

void play_game(unsigned char *parlcd_mem_base, unsigned char* mem_base);
void draw_pixel(int x, int y, unsigned short color);
void draw_char(int x, int y, char ch, unsigned short color, int scale);
void draw_pixel_big(int x, int y, unsigned short color, int scale);
int char_width(int ch);
void endgame_clear_screen(unsigned char *parlcd_mem_base);
void clear_screen(unsigned char *parlcd_mem_base, unsigned short* fb);
void init_fb(unsigned short* fb);
void check_food_collision(snake_t* snake, snake_food_t* food);
void check_snake_collision(snake_t* snake);
_Bool intersects(int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2);


//Initialize display
unsigned short *fb;

unsigned char *parlcd_mem_base;
unsigned char *mem_base;
struct timespec loop_delay;


int main(void){
  printf("Hello mf\n");

  //Initialize framebuffer
  int ptr = 0;
  fb = (unsigned short *)malloc(320*480*2);
  //Initialize peripherals
  mem_base = init_mem_base();
  parlcd_mem_base = init_parlcd_mem_base();
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  //Initialize FPS 
  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 150 * 1000 * 5000;
  
  //Initialize menu knob
  knob_t green_knob = init_knob(8, 0x2000000, mem_base);
  short knob_update_value;
 
  //Initialize menu
  //TODO: move to a separate '.c' file
  char text1[5] = "PLAY";
  char text2[5] = "QUIT";
  char title[10] = "MAIN MENU";
  short selected_button = 0;
  short num_buttons = 2;
  char *menu_texts[] = {text1, text2};
  menu_t main_menu = new_menu(title, WHITE, GREEN, BLUE, WHITE, menu_texts, num_buttons);
  printf("Menu initialized\n");

  while(TRUE) {
    
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    knob_update_value = green_knob.update_rotation(&green_knob, mem_base);

    selected_button =  knob_update_value != 0 ? abs(selected_button + knob_update_value) % num_buttons : selected_button;

    reset_fb(fb, RED);
    main_menu.update(&main_menu, selected_button);
    main_menu.show(&main_menu);
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }

    if (green_knob.is_pressed(&green_knob, r)) { //if green button is pressed
      if (selected_button == 0) { //if game button is picked
        play_game(parlcd_mem_base, mem_base);
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

  reset_fb(fb,BLACK);
  snake.draw(&snake, parlcd_mem_base);

  while(1) {
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    if (red_knob.is_pressed(&red_knob, r)) {
      clear_screen(parlcd_mem_base, fb);
      exit(0);
    }
    snake.draw(&snake, parlcd_mem_base);

    //UPDATE SNAKE
    green_knob.update_rotation(&green_knob, mem_base);
    check_food_collision(&snake, &food);
    check_snake_collision(&snake);
    snake.update(&snake, &green_knob);
    food.draw(&food, parlcd_mem_base);
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    clear_screen(parlcd_mem_base, fb);
    reset_fb(fb, BLACK);
  }
}

void check_food_collision(snake_t* snake, snake_food_t* food) {
    int snake_x = snake->squares[0].x_coord;
    int snake_y = snake->squares[0].y_coord;
    int food_x = food->x;
    int food_y = food->y;
    int food_size = food->size;
    int snake_size = snake->square_size;

    if(intersects(snake_x, snake_y, food_x, food_y, snake_size, food_size, snake_size, food_size)){
      food->change_position(food);
      snake->length++;
    }
}



void check_snake_collision(snake_t* snake) {
    int head_x = snake->squares[0].x_coord;
    int head_y = snake->squares[0].y_coord;
    int snake_size = snake->square_size;
    for (int i = 1; i < snake->length; i++) {
        // Get the coordinates and dimensions of the current snake segment
        int segment_x = snake->squares[i].x_coord;
        int segment_y = snake->squares[i].y_coord;

        // Check if the snake's head intersects with the current segment
        if (intersects(head_x, head_y, segment_x, segment_y, snake_size, snake_size, snake_size, snake_size)) {
            // Handle collision (e.g., game over, decrease health, etc.)
            // You can add your collision logic here
            // For now, let's print a message
            printf("Snake collided with itself!\n");
            break; // No need to check further
        }
    }
}

_Bool intersects(int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2){
  if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) {
    return 1;
  }
  return 0;
}

