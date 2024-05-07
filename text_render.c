#include "text_render.h"
#include "display_utils.h"
#include "graphic_structures.h"
#include "font_types.h"

void draw_char(graphics_object_t *self, point_t point, char ch, color_t color, font_descriptor_t *fdes){
    int w = char_width(fdes, ch);
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
                draw_pixel(self, point, color);
            }
            val<<=1;
        }
        ptr++;
        }
    }
}

void draw_string(graphics_object_t *self, point_t point, char *string, color_t color, font_descriptor_t* fdes){
    while (*string != '\0'){
        draw_char(self, point, *string, color, fdes);
        point.x += char_width(fdes, *string);
        string++;
    }
}

int char_width(font_descriptor_t* fdes, char ch) {
  int width = 0;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    ch -= fdes->firstchar;
    if (!fdes->width) {
      width = fdes->maxwidth;
    } else {
      width = fdes->width[ch];
    }
  }
  return width;
}