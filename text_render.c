#include "text_render.h"
#include "display_utils.h"
#include "font_types.h"

void draw_char(int x, int y, char ch, unsigned short color, int scale) {
  int w = char_width(ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth+15)/16;
      ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
    }
    int i, j;
    for (i=0; i<fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big(x+scale*j, y+scale*i, color, scale);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

int char_width(int ch) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch-fdes->firstchar];
  }
  return width;
}

void draw_text_line(int x, int y, char* text, unsigned short color, int scale){
  short prev_width = 0;
  short prev_space = 0;
  short ptr = 0;
  while (text[ptr] != '\0'){
    draw_char(x + prev_space, y, text[ptr], color, scale);
    prev_width = char_width(text[ptr]);
    prev_space += prev_width * scale;
    ptr++;
  }
}

void draw_text(text_t* t) {
  draw_text_line(t->start_x, t->start_y, t->text, t->color, t->scale);
}

short measure_text_width(char* text, int scale){
  short width = 0;
  short prev_space = 0;
  short prev_width = 0;
  short ptr = 0;
  while (text[ptr] != '\0'){
    prev_width = char_width(text[ptr]);
    prev_space += prev_width;
    width += prev_width * scale / 2;
    ptr++;
  }
  printf("Width: %d\n", width);
  return width;
}

text_t new_text(int x, int y, char* text, unsigned short color, int scale){
  text_t t;
  t.text = text;
  t.scale = scale;
  t.start_x = x;
  t.start_y = y;
  t.color = color;
  t.draw = draw_text;
  return t;
}