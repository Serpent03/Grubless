#include "../headers/driver/video.h"
#include "../headers/sys/hal.h"
#include "../headers/util/assert.h"
#include "../headers/util/mem.h"

uint16 x, y;
uint8 color;
uint16 *vmem_ptr;

uint16 xyton(uint16 x, uint16 y) { return y * WIDTH + x; }

void set_cursor(uint16 n) {
  /* CRT_ADDR_REG decides where the data goes, and then CRT_DATA_REG actually
    delivers the data. I am guessing that the design is implemented this way
    owing to compatibility mode with older devices. */
  uint16 cursor = xyton(x, y);
  port_byte_write(CRT_ADDR_REG, 0xF);
  port_byte_write(CRT_DATA_REG, cursor & 0xFF);
  port_byte_write(CRT_ADDR_REG, 0xE);
  port_byte_write(CRT_DATA_REG, (cursor >> 8) & 0xFF);
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
  memsetw((uint16 *)VMEMLOC, blank, WIDTH * HEIGHT);
  set_cursor(xyton(0, 0));
  x = 0;
  y = 0;
}

void scroll(uint16 n) {
  if (n <= 0)
    return;
  for (uint16 i = 0; i < n; i++) {
    uint16 *row = (uint16 *)VMEMLOC;
    for (uint16 j = 0; j < HEIGHT - 1; j++) {
      memcpyw(row, row + WIDTH, WIDTH);
      row += WIDTH;
    }
  }
  x = y - n < 0 ? 0 : x; // if we're clearing the whole screen, reset it
  y = y - n >= 0 ? y - n : 0;
  set_cursor(xyton(x, y));
}

void printch(uint8 c) {
  uint16 vchar = ((uint16)(color) << 8) | c;
  uint16 cursor;
  switch (c) {
  case '\r':
    x = 0;
    return;
  case '\n':
    x = 0;
    y++;
    return;
  default:
    break;
  }
  if (x >= WIDTH) {
    x = 0;
    y++;
    cursor = xyton(x, y);
  }
  if (y >= HEIGHT) {
    scroll(5);
    cursor = xyton(x, y);
  }
  cursor = xyton(x, y);
  vmem_ptr[cursor] = vchar;
  x++;
  set_cursor(cursor);
}

void prints(int8 *str) {
  char c;
  while ((c = (*str++))) {
    printch(c);
  }
}

void printd(int32 d) {
  int32 t = 0;
  while (d > 0) {
    t *= 10;
    t += d % 10;
    d /= 10;
  }
  while (t > 0) {
    printch('0' + t % 10);
    t /= 10;
  }
}

char itoh(uint8 i) {
  char c;
  if (i >= 0 && i <= 9) {
    c = '0' + i;
  } else if (i >= 10 && i <= 15) {
    c = 'A' + i % 10;
  }
  return c;
}

void printh(uint32 h) {
  int n = 0;
  uint32 t = h;
  while (t > 0) {
    n++;
    t /= 16;
  }
  char hex[n];
  uint32 idx = 0;
  while (h > 0) {
    hex[idx++] = itoh(h % 16);
    h /= 16;
  }
  prints("0x");
  while (idx--) {
    printch(hex[idx]);
  }
}

void init_video() {
  set_fg_color(VGA_COLOR_WHITE);
  set_bg_color(VGA_COLOR_BLUE);
  vmem_ptr = (uint16 *)VMEMLOC;
  cls();
}
