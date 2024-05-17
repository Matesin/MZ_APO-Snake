#include "snake_food.h"
void change_food_position(snake_food_t* self){
    self->x = rand() % LCD_WIDTH;
    self->y = rand() % LCD_HEIGHT;
}
void draw_food(snake_food_t* self){
    
}

snake_food_t init_food(){
    snake_food_t f;
    f.change_position = change_food_position;
    f.draw = draw_food;
    f.x = 0;
    f.y = 0;
    f.change_position(&f);
    return f;
}


