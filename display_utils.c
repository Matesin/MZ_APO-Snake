#include "display_utils.h"
unsigned char* init_mem_base(){
  unsigned char *mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (mem_base == NULL) {
    fprintf(stderr, "Error: Unable to map physical address\n");
    exit(1);
  }
  return mem_base;
}
unsigned char* init_parlcd_mem_base(){
  unsigned char *parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL) {
    fprintf(stderr, "Error: Unable to map physical address\n");
    exit(1);
  }
  return parlcd_mem_base;
}

void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}

void draw_pixel_big(int x, int y, unsigned short color, int scale) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel(x+i, y+j, color);
    }
  }
}

void clear_screen(unsigned char *parlcd_mem_base, unsigned short* fb){
  int ptr = 0;
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 0; ptr < LCD_SIZE; ptr++){
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
  }
}

void reset_fb(unsigned short* fb){
  int ptr = 0;
  for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u;
  }
}

void endgame_clear_screen(unsigned char *parlcd_mem_base){
  int ptr;
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
    parlcd_write_data(parlcd_mem_base, 0);
  }
}