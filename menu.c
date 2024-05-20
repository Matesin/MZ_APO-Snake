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

int arr_num_elements(char** arr){
  int num_elements = 0;
  while(arr[num_elements] != NULL) {
    num_elements++;
  }
  printf("Num elements %d\n", num_elements);
  return num_elements;
}

void update_menu(menu_t* self, short selected_button){
  //Update menu properties
  // printf("Selected button: %d\n", selected_button);
  short prev_selected = self->selected_button;
  self->selected_button = selected_button;
  // printf("Selected button: %d\n", self->selected_button);
  // printf("Prev selected button: %d\n", prev_selected);
  self->buttons[prev_selected].rectangle.color = self->button_base_color;
  self->buttons[self->selected_button].rectangle.color = self->button_selected_color;
}

button_t new_button(char* text, _Bool selected, int x_coord, int y_coord, unsigned short base_color, unsigned short selected_color, unsigned short text_color, short button_width, short button_height) {//Button width and height to be defined as constants
  button_t b;
  b.selected = selected;
  b.base_color = base_color;
  b.selected_color = selected_color;
  //center the text
  short text_x =  x_coord + (button_width / 2) - (measure_text_width(text, MENU_TEXT_SIZE));
  b.cur_color = b.selected ? selected_color : base_color;
  b.text = new_text(text_x, y_coord + BUTTON_TEXT_Y_OFFSET, text, text_color, BUTTON_TEXT_SIZE); //TODO
  b.rectangle = new_rectangle(x_coord, y_coord, button_width, button_height, b.cur_color);
  b.draw = draw_button;
  return b;
}

menu_t new_menu(char* title, unsigned short title_color, unsigned short button_base_color, unsigned short button_selected_color, unsigned short button_text_color, char** button_texts, short num_buttons){
  menu_t m;
  m.padding = MENU_Y_PADDING;
  int title_x = LCD_WIDTH / 2 - measure_text_width(title, MENU_TEXT_SIZE);
  m.title = new_text(title_x, MENU_Y_PADDING, title, title_color, MENU_TEXT_SIZE);
  
  m.button_base_color = button_base_color;
  m.button_selected_color = button_selected_color;
  m.button_text_color = button_text_color;
  //measure max size of buttons
  short button_width = 0;
  for (size_t i = 0; i < num_buttons; ++i){
    int t = measure_text_width(button_texts[i], MENU_TEXT_SIZE) * 2;
    button_width = t > button_width ? t : button_width;
  }

  button_width += BUTTON_TEXT_X_OFFSET * 2; //offset for each side
  short menu_y = title[0] == ' ' ? MENU_Y_PADDING : BUTTON_HEIGHT + MENU_Y_PADDING;
  m.num_buttons = num_buttons;
  m.selected_button = 0;
  short button_x = LCD_WIDTH / 2 - button_width / 2;
  m.buttons = malloc(m.num_buttons * sizeof(button_t));  
  for (short i = 0; i < m.num_buttons; i++) {
    _Bool selected = i == m.selected_button ? TRUE : FALSE;
    m.buttons[i] = new_button(button_texts[i], selected, button_x, menu_y + (MENU_Y_PADDING + BUTTON_HEIGHT) * i, button_base_color, button_selected_color, button_text_color, button_width, BUTTON_HEIGHT);
    printf("Button %d text: %s\n", i, button_texts[i]);
  };
  m.show = draw_menu;
  m.update = update_menu;
  return m;
}