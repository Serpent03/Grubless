#include "../headers/sys/video.h"
#include "../headers/util/mem.h"

uint16 cursor;
uint8 color;

uint16 xyton(uint16 x, uint16 y) {
  uint16 result;

  return result;
}

void set_cursor(uint16 n) {
  
}

void set_fg_color(uint8 col) {
  color &= 0xF0;
  color |= (col & 0xF);
}

void set_bg_color(uint8 col) {
  color &= 0x0F;
  color |= ((col & 0xF) << 4);
}

void cls() {
  /* when all you have is a hammer, everything appears to be a nail. */
  uint16 blank = ((uint16)(color) << 8) | ' ';
  memsetw((uint16*)VMEMLOC, blank, WIDTH * HEIGHT);
  cursor = xyton(0, 0);
}

void init_video() {
  set_fg_color(VGA_COLOR_WHITE);
  set_bg_color(VGA_COLOR_BLACK);
  cls();
}
