#include "menu.h"

void draw_button(button_t* self){
  self->rectangle.draw(&self->rectangle);
  self->text.draw(&self->text);
}
void draw_menu(menu_t* self){
  int i;
  self->title.draw(&self->title);
  for (i = 0; i < self->num_buttons; i++){
    self->buttons[i].draw(&self->buttons[i]);
  }
}

short arr_num_elements(char** arr){
  return sizeof(arr) / sizeof(arr[0]);
}

void update_menu(menu_t* self, short selected_button){
  //Update menu properties
  printf("Selected button: %d\n", selected_button);
  short prev_selected = self->selected_button;
  self->selected_button = selected_button;
  printf("Selected button: %d\n", self->selected_button);
  printf("Prev selected button: %d\n", prev_selected);
  self->buttons[prev_selected].rectangle.color = self->button_base_color;
  self->buttons[self->selected_button].rectangle.color = self->button_selected_color;
}

button_t new_button(char* text, _Bool selected, int x, int y, unsigned short base_color, unsigned short selected_color, unsigned short text_color) {//Button width and height to be defined as constants
  button_t b;
  b.selected = selected;
  b.base_color = base_color;
  b.selected_color = selected_color;
  b.cur_color = b.selected ? selected_color : base_color;
  b.text = new_text(x + BUTTON_TEXT_X_OFFSET, y + BUTTON_TEXT_Y_OFFSET, text, text_color, BUTTON_TEXT_SIZE); //TODO
  b.rectangle = new_rectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, b.cur_color);
  b.draw = draw_button;
  return b;
}

menu_t new_menu(char* title, unsigned short title_color, unsigned short button_base_color, unsigned short button_selected_color, unsigned short button_text_color, char** button_texts){
  menu_t m;
  m.padding = MENU_Y_PADDING;
  int title_x = LCD_WIDTH / 2 - measure_text_width(title, MENU_TEXT_SIZE);
  m.title = new_text(title_x, MENU_Y_PADDING, title, title_color, MENU_TEXT_SIZE);
  m.title_color = title_color;
  m.button_base_color = button_base_color;
  m.button_selected_color = button_selected_color;
  m.button_text_color = button_text_color;

  m.num_buttons = arr_num_elements(button_texts);
  m.selected_button = 0;
  short button_x = LCD_WIDTH / 2 - BUTTON_WIDTH / 2;
  m.buttons = malloc(m.num_buttons * sizeof(button_t));  
  for (short i = 0; i < m.num_buttons; i++) {
    _Bool selected = i == m.selected_button ? TRUE : FALSE;
    m.buttons[i] = new_button(button_texts[i], selected, button_x, BUTTON_HEIGHT + (MENU_Y_PADDING + BUTTON_HEIGHT) * i, button_base_color, button_selected_color, button_text_color);
  };
  m.show = draw_menu;
  m.update = update_menu;
  return m;
}