#include "game.h"

struct timespec game_loop_delay = {0, 150 * 1000 * 1000};


void play_game(unsigned char *parlcd_mem_base, unsigned char *mem_base){
  //TODO: ADD MACROS INSTEAD OF MAGIC NUMBERS
  int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
  game_loop_delay.tv_sec = 0;
  game_loop_delay.tv_nsec = 150 * 1000 * 1000; 
  snake_t snake = init_snake(BLUE, RIGHT);
  knob_t red_knob = init_knob(16, 0x4000000, mem_base);
  knob_t green_knob = init_knob(8, 0x2000000, mem_base);
  knob_t blue_knob = init_knob(0, 0x1000000, mem_base);
  snake_food_t food = init_food(WHITE);

  snake.draw(&snake, parlcd_mem_base);

  while(1) {
    reset_fb(fb, GAME_BACKGROUND_COLOR);
    update_led(mem_base, snake.length - SNAKE_START_LEN, snake.length - SNAKE_START_LEN);
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
    clock_nanosleep(CLOCK_MONOTONIC, 0, &game_loop_delay, NULL);
    clear_screen(parlcd_mem_base, fb);
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

void update_led(unsigned char *mem_base, int led_count_left, int led_count_right){
    led_count_left = led_count_left % 17;
    led_count_right = led_count_right % 17;
    volatile uint32_t *p = (uint32_t *)(mem_base + SPILED_REG_LED_LINE_o);
    *p = ((1 << led_count_left) - 1) << 16 | ((1 << led_count_right) - 1);
}
