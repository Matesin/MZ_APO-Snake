
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
#include "game.h"


font_descriptor_t* fdes = &font_winFreeSystem14x16;

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
  loop_delay.tv_nsec = 150 * 1000 * 3000;
  
  //Initialize menu knob
  knob_t green_knob = init_knob(8, 0x2000000, mem_base);
  short knob_update_value;
 
  //Initialize menu
  //TODO: move to a separate '.c' file
  char menu_text_1[5] = "Play";
  char menu_text_2[5] = "Quit";
  char player_menu_text_1[8] = "1 Player";
  char player_menu_text_2[9] = "2 Players";
  char player_menu_text_3[9] = "Back";

  char title[10] = "MAIN MENU";
  short selected_button = 0;
  char *menu_texts[] = {menu_text_1, menu_text_2};
  char *player_menu_texts[] = {player_menu_text_1, player_menu_text_2, player_menu_text_3};
  menu_t main_menu = new_menu(title, WHITE, MENU_BUTTON_COLOR, MENU_PICKED_BUTTON_COLOR, WHITE, menu_texts);
  menu_t number_of_players_menu = new_menu(" ", WHITE, MENU_BUTTON_COLOR, MENU_PICKED_BUTTON_COLOR, WHITE, player_menu_texts); 

  while(TRUE) {
    //SHOW MAIN MENU
    //TODO: move to a separate '.c' file
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    knob_update_value = green_knob.update_rotation(&green_knob, mem_base);
    selected_button =  knob_update_value != 0 ? abs(selected_button + knob_update_value) % arr_num_elements(menu_texts) : selected_button;

    reset_fb(fb, MENU_BACKGROUND_COLOR);
    main_menu.update(&main_menu, selected_button);
    main_menu.show(&main_menu);
    
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
    if (green_knob.is_pressed(&green_knob, r)) { //if green button is pressed
      if (selected_button == 0) { //if game button is picked
        while (TRUE)
        {
          //SHOW NUMBER OF PLAYERS MENU 
          //TODO: move to a separate '.c' file
          r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
          knob_update_value = green_knob.update_rotation(&green_knob, mem_base);
          selected_button =  knob_update_value != 0 ? abs(selected_button + knob_update_value) % arr_num_elements(menu_texts) : selected_button;
          reset_fb(fb, MENU_BACKGROUND_COLOR);
          number_of_players_menu.update(&number_of_players_menu, selected_button);
          number_of_players_menu.show(&number_of_players_menu);  
          parlcd_write_cmd(parlcd_mem_base, 0x2c);
          for (ptr = 0; ptr < LCD_SIZE; ptr++){
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
          }
          if (green_knob.is_pressed(&green_knob, r)) {
            switch (selected_button)
            {
              case 1:
                play_game(parlcd_mem_base, mem_base); //TODO: implement one-player game
                break;
              case 2:
                play_game(parlcd_mem_base, mem_base); //TODO: implement two-player game
                break;
              default:
                break;
            }
          }
        }
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
  free(fb);
  return 0;
}



