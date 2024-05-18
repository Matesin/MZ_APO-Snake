#include "menu.h"

void draw_button(button_t* self){
  self->rectangle.draw(&rectangle);
  self->text.draw(&text);
}
void draw_menu(menu_t* self){
  int i;
  for (i = 0; i < self->num_buttons; i++){
    self->buttons[i].draw(&self->buttons[i]);
  }
}
button_t new_button(char* text, _Bool selected, int x, int y, unsigned short base_color, unsigned short selected_color, unsigned short text_color) {//Button width and height to be defined as constants
  button_t b;
  b.text = text;
  b.selected = selected;
  b.button_text = new_text(x + BUTTON_TEXT_X_OFFSET, y + BUTTON_TEXT_Y_OFFSET, text_color); //TODO
  b.base_color = base_color;
  b.selected_color = selected_color;
  b.cur_color = b.selected ? selected_color : base_color;
  b.rectangle = new_rectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, cur_color);
  return b;
}