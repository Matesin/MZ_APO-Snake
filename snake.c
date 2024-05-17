#include "snake.h"
void draw_snake(snake_t *self, unsigned char *parlcd_mem_base){
  /**
   * Draw snake of respective size based on its current position
   */
  int ptr = 0;
  for (int i = 0; i < self->length; i++) {
      draw_pixel_big(self->squares[i].x_coord, self->squares[i].y_coord, self->color, self->square_size);
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
}

void update_snake(snake_t* self, knob_t* k){
  /**
   * Check input and update snake position
   */
  update_snake_dir(self, k);
  update_snake_pos(self);
}

void update_snake_dir(snake_t* self, knob_t* k){
  int SENSITIVITY = 3;  //todo, change to local macro during decomposition
  if ((k->value < k->prev_value) && abs(k->value - k->prev_value) > SENSITIVITY){
    self->direction = self->direction == UP ? LEFT : self->direction - 1;
  } else if ((k->value > k->prev_value) && abs(k->value - k->prev_value) > SENSITIVITY){
    self->direction = self->direction == LEFT ? UP : self->direction + 1;
  }
}

void update_snake_pos(snake_t* self){
  /**
   * Update snake position based on current direction (self-explanatory)
  */
  switch (self->direction) {
    case RIGHT:
      for (int i = self->length - 1; i > 0; i--) {
        self->squares[i].x_coord = self->squares[i-1].x_coord;
        self->squares[i].y_coord = self->squares[i-1].y_coord;
      }
      self->squares[0].x_coord = (self->squares[0].x_coord + self->square_size) % LCD_WIDTH;
      break;
    case LEFT:
      for (int i = self->length - 1; i > 0; i--) {
        self->squares[i].x_coord = self->squares[i-1].x_coord;
        self->squares[i].y_coord = self->squares[i-1].y_coord;
      }
      self->squares[0].x_coord = (self->squares[0].x_coord - self->square_size + LCD_WIDTH) % LCD_WIDTH;
      break;
    case UP:
      for (int i = self->length - 1; i > 0; i--) {
        self->squares[i].x_coord = self->squares[i-1].x_coord;
        self->squares[i].y_coord = self->squares[i-1].y_coord;
      }
      self->squares[0].y_coord = (self->squares[0].y_coord - self->square_size + LCD_HEIGHT) % LCD_HEIGHT;
      break;
    case DOWN:
      for (int i = self->length - 1; i > 0; i--) {
        self->squares[i].x_coord = self->squares[i-1].x_coord;
        self->squares[i].y_coord = self->squares[i-1].y_coord;
      }
      self->squares[0].y_coord = (self->squares[0].y_coord + self->square_size) % LCD_HEIGHT;
      break;
  }
}
snake_t init_snake(int color, int direction){
  /**
   * Default constructor
   */
    snake_t s;
    s.squares = (snake_sq_t*) malloc(SNAKE_MAX_LEN * sizeof(snake_sq_t));
    s.direction = (direction >= 0 && direction <= 3) ? direction : LEFT; //safety check for unkown direction value
    s.square_size = SNAKE_SQUARE_SIZE; 
    s.length = SNAKE_START_LEN; 
    s.color = BLUE;
    s.draw = draw_snake;
    s.update = update_snake;
    for (int i = 0; i < s.length; i++) {
      s.squares[i].x_coord = 150 - s.square_size * i; 
      s.squares[i].y_coord = 150;
    }
    return s;
}