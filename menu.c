#include "menu.h"

void draw_button(button_t* self){
  self->rectangle.draw(&self->rectangle);
  self->text.draw(&self->text);
}
void draw_menu(menu_t* self){
  int i;
  for (i = 0; i < self->num_buttons; i++){
    self->buttons[i].draw(&self->buttons[i]);
  }
}

void update_menu(menu_t* self, short selected_button){
  //Update menu properties
  //POSSIBLE IMPLEMENTATION: knob update inside this func
  self->buttons[self->selected_button].cur_color = self->button_base_color;
  self->buttons[selected_button].cur_color = self->button_selected_color;
  self->selected_button = selected_button;
  self->buttons[self->selected_button].rectangle.color = self->buttons[self->selected_button].cur_color;
  self->buttons[self->selected_button].rectangle.draw(&self->buttons[self->selected_button].rectangle);
}
button_t new_button(char* text, _Bool selected, int x, int y, unsigned short base_color, unsigned short selected_color, unsigned short text_color) {//Button width and height to be defined as constants
  button_t b;
  b.selected = selected;
  b.text = new_text(x + BUTTON_TEXT_X_OFFSET, y + BUTTON_TEXT_Y_OFFSET, text, text_color, BUTTON_TEXT_SIZE); //TODO
  b.base_color = base_color;
  b.selected_color = selected_color;
  b.cur_color = b.selected ? selected_color : base_color;
  b.rectangle = new_rectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, b.cur_color);
  return b;
}
menu_t new_menu(char* title, int padding, unsigned short title_color, unsigned short button_base_color, unsigned short button_selected_color, unsigned short button_text_color, button_t* buttons, short num_buttons){
  menu_t m;
  m.padding = MENU_Y_PADDING;
  m.title = new_text(MENU_X_PADDING, MENU_Y_PADDING, title, title_color, MENU_TEXT_SIZE);
  m.title_color = title_color;
  m.button_base_color = button_base_color;
  m.button_selected_color = button_selected_color;
  m.button_text_color = button_text_color;
  m.buttons = buttons;
  m.num_buttons = num_buttons;
  m.selected_button = 0;
  m.show = draw_menu;
  m.update = update_menu;
  return m;
}