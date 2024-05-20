#include "game.h"

struct timespec game_loop_delay = {0, 150 * 1000 * 1000};
/************************************************
 * Function: play_game
 * ----------------------------------------------
 *  Main game loop 
*************************************************/

void play_game(unsigned char *parlcd_mem_base, unsigned char *mem_base, _Bool multiplayer){
  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  short num_snakes = multiplayer ? 2 : 1;
  int ptr;
  short i;
  snake_t* snakes = malloc(num_snakes * sizeof(snake_t));

  for (i = 0; i < num_snakes; i++){
    unsigned short snake_color = i == 0 ? BLUE : GREEN;
    short snake_dir = i == 0 ? DOWN : UP;
    snakes[i] = init_snake(snake_color, snake_dir);
  }
  game_loop_delay.tv_sec = 0;
  game_loop_delay.tv_nsec = 150 * 1000 * 1000;

  knob_t red_knob = init_knob(16, 0x4000000, mem_base);
  knob_t green_knob = init_knob(8, 0x2000000, mem_base);
  knob_t blue_knob = init_knob(0, 0x1000000, mem_base);
  snake_food_t food = init_food(RED);

  char endgame_menu_text1[10] = "Main Menu";
  char endgame_menu_text2[5] = "Quit";
  char endgame_title [10] = "GAME OVER";

  char pause_menu_text1[7] = "Resume";
  char pause_menu_text2[5] = "Quit";
  char pause_title[7] = "PAUSED";


  char* endgame_menu_texts[] = {endgame_menu_text1, endgame_menu_text2};
  char* pause_menu_texts[] = {pause_menu_text1, pause_menu_text2};
  short num_buttons = 2;

  menu_t endgame_menu = new_menu(endgame_title, WHITE, MENU_BUTTON_COLOR, MENU_PICKED_BUTTON_COLOR, WHITE, endgame_menu_texts, num_buttons);
  menu_t pause_menu = new_menu(pause_title, WHITE, MENU_BUTTON_COLOR, MENU_PICKED_BUTTON_COLOR, WHITE, pause_menu_texts, num_buttons);

  for (i = 0; i < num_snakes; i++){
    snakes[i].draw(&snakes[i], parlcd_mem_base);
  }

  short knob_update_value;
  short selected_button = 0;
  _Bool collision = FALSE;
  //MAIN GAME LOOP
  while(TRUE) {
    reset_fb(fb, GAME_BACKGROUND_COLOR);
    if (multiplayer){
      update_led(mem_base, snakes[1].length - SNAKE_START_LEN, snakes[0].length - SNAKE_START_LEN);
    } else update_led(mem_base, 0,snakes[0].length - SNAKE_START_LEN);
    r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
    if (red_knob.is_pressed(&red_knob, r)) {
      while (TRUE)
        {
          //SHOW PAUSE MENU 
          //TODO: move to a separate '.c' file
          r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
          knob_update_value = green_knob.update_rotation(&green_knob, mem_base);
          selected_button =  knob_update_value != 0 ? abs(selected_button + knob_update_value) % num_buttons : selected_button;
          reset_fb(fb, MENU_BACKGROUND_COLOR);
          pause_menu.update(&pause_menu, selected_button);
          pause_menu.show(&pause_menu);  
          parlcd_write_cmd(parlcd_mem_base, 0x2c);

          for (ptr = 0; ptr < LCD_SIZE; ptr++){
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
          }
          if (green_knob.is_pressed(&green_knob, r)) {
            if (selected_button == 1){
              goto break_loop;
            } else break;
          }
        }
    }
    for (i = 0; i < num_snakes; ++i){
      snakes[i].draw(&snakes[i], parlcd_mem_base);
    }

    //UPDATE SNAKE
    for (i = 0; i < num_snakes; i++){
      num_snakes == 1 ? green_knob.update_rotation(&green_knob, mem_base) : i == 0 ? red_knob.update_rotation(&red_knob, mem_base) : blue_knob.update_rotation(&blue_knob, mem_base);
    }
    for (i = 0; i < num_snakes; i++){
      check_food_collision(&snakes[i], &food);
    }
  
    if ((collision = multiplayer ? check_snake_collision(&snakes[0]) || check_snake_collision(&snakes[1]) : check_snake_collision(&snakes[0])) == TRUE){
      while (TRUE)
        {
          //SHOW ENDGAME MENU 
          //TODO: move to a separate '.c' file
          r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
          knob_update_value = green_knob.update_rotation(&green_knob, mem_base);
          selected_button =  knob_update_value != 0 ? abs(selected_button + knob_update_value) % num_buttons : selected_button;
          reset_fb(fb, MENU_BACKGROUND_COLOR);
          endgame_menu.update(&endgame_menu, selected_button);
          endgame_menu.show(&endgame_menu);  
          parlcd_write_cmd(parlcd_mem_base, 0x2c);

          for (ptr = 0; ptr < LCD_SIZE; ptr++){
            parlcd_write_data(parlcd_mem_base, fb[ptr]);
          }
          if (green_knob.is_pressed(&green_knob, r)) {
            if (selected_button == 0){
              goto break_loop;
            } else {
              endgame_clear_screen(parlcd_mem_base);
              exit(0);
            }
          }
        }
    }
  for (i = 0; i < num_snakes; i++){
    num_snakes == 1 ? snakes[i].update(&snakes[i], &green_knob) : i == 0 ? snakes[i].update(&snakes[i], &red_knob) : snakes[i].update(&snakes[i], &blue_knob);
  }
    food.draw(&food, parlcd_mem_base);
    clock_nanosleep(CLOCK_MONOTONIC, 0, &game_loop_delay, NULL);
    clear_screen(parlcd_mem_base, fb);
  }
  break_loop:
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

_Bool check_snake_collision(snake_t* snake) {
    int head_x = snake->squares[0].x_coord;
    int head_y = snake->squares[0].y_coord;
    int snake_size = snake->square_size;
    for (int i = 1; i < snake->length; i++) {
        // Get the coordinates and dimensions of the current snake segment
        int segment_x = snake->squares[i].x_coord;
        int segment_y = snake->squares[i].y_coord;

        // Check if the snake's head intersects with the current segment
        if (intersects(head_x, head_y, segment_x, segment_y, snake_size, snake_size, snake_size, snake_size)) {
            printf("Snake collided with itself!\n");
            return TRUE;
        }
    }
  return FALSE;
}

_Bool intersects(int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2){
  if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) {
    return 1;
  }
  return 0;
}

void update_led(unsigned char* mem_base, int snake1_len, int snake2_len) {
    if(!(snake1_len) && !(snake2_len)) return;  
    // Calculate the LED pattern for each snake
    uint32_t led_pattern_snake1 = snake1_len > 0 ? ((1 << (snake1_len % 17)) - 1) : 0;
    uint32_t led_pattern_snake2 = snake2_len > 0 ? (0xFFFFFFFF << (32 - (snake2_len % 17))) : 0xFFFFFFFF;

    // Update the LED line register with the new pattern
    *((volatile uint32_t *)(mem_base + SPILED_REG_LED_LINE_o)) = led_pattern_snake1 | led_pattern_snake2;
}
