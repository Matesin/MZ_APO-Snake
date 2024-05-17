#include "snake.h"

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
void update_snake(snake_t *self, int knob_val);