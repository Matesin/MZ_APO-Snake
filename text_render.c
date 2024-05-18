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

void draw_text(text_t* t) {
  int ptr = 0;
  while (t->text[ptr] != '\0'){
    draw_char(t->start_x + ptr * 2 * BLOCK_SIZE, t->start_y, t->text[ptr], t->color, t->scale);
    ptr++;
  }
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