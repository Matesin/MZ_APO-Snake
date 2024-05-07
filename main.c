
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
#include "game.h"
#include "game_graphics.h"
#include "constants.h"
#include "display_utils.h"

//Initialize game graphics
graphics_object_t graphics = {
  .init = init_graphics,
  .draw_pixel = draw_pixel,
  .draw_line = draw_line,
  .clear_screen = clear_screen,
};
//Initialize game properties
game_t game = {
    //Initialize game settings
    .settings = {
      .player_lives = 100,
      .enemy_bullet_speed = 1,
      .player_bullet_speed = 1,
      .player_fire_rate = 1,
      .enemy_fire_rate = 1,
      .player_speed = 1,
      .enemy_speed = 1,
      .player_score = 0
    },
    .player = {
      .base = {
        .update = (void (*)(game_object_t*, graphics_object_t*)) update_player_ship,
        .render = (void (*)(game_object_t*, graphics_object_t*)) render_player_ship,
        .position = {240, 160} //Initalize player position at centre bottom CHANGE LATER
      },
      .health = 100
    }
};

//Initialize display
unsigned short *fb;
unsigned char *parlcd_mem_base;
unsigned char *mem_base;

int main(void){
  //Initialize framebuffer
  unsigned int c;
  int i,j;
  int ptr;
  fb  = (unsigned short *)malloc(320*480*2);

  //Initialize peripherals
  mem_base = init_mem_base();
  parlcd_mem_base = init_parlcd_mem_base();
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  ptr=0;
 
  printf("Hello world\n");
}

