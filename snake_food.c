#include "snake_food.h"
void change_food_position(snake_food_t* self){
    self->x = rand() % LCD_WIDTH;
    self->y = rand() % LCD_HEIGHT;
}
void draw_food(snake_food_t* self, unsigned char *parlcd_mem_base){
    draw_pixel_big(self->x, self->y, self->color, self->size);
}
snake_food_t init_food(unsigned short color){
    snake_food_t f;
    f.change_position = change_food_position;
    f.draw = draw_food;
    f.size = SNAKE_FOOD_SIZE;
    f.x = 0;
    f.y = 0;
    f.color = color;
    f.change_position(&f);
    return f;
}


