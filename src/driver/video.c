#include "../headers/driver/video.h"
#include "../headers/sys/hal.h"
#include "../headers/util/assert.h"
#include "../headers/util/mem.h"
#include "../headers/util/string.h"

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

/* todo: create a printf() function for better usability.. */
void prints(int8 *str) {
  char c;
  while ((c = (*str++))) {
    printch(c);
  }
}

void printd(int32 d) {
  int32 t = 0;
  if (d == 0) {
    printch('0');
  } else {
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
  /* This is going to need rework */
  if (h == 0) {
    prints("00");
  } else {
    while (h > 0) {
      hex[idx++] = itoh(h % 16);
      h /= 16;
    }
  }
  while (idx--) {
    printch(hex[idx]);
  }
}

uint8 is_formatting_argument(uint8 c) {
  switch (c) {
  case 'c':
    return 1;
  case 's':
    return -1;
  case 'h':
  case 'd':
    return 4;
  }
  return 0;
}

void printf(int8 *pattern, uint32 n, ...) {
  /* this function is what K&C meant by blowing your foot off.. */
  uint32 len = strlen(pattern);

  uint32 tokens[n];
  uint32 token_idx = 0;

  void *p = (void*)&n;

  for (uint32 i = 0; i < len; i++) {
    if (pattern[i] == '%') {
      uint8 size = is_formatting_argument(pattern[i+1]);
      if (size < 0) {
        // string
      } else if (size > 0) {
        p += size;
        tokens[token_idx++] = *(uint32*)p;
      }
    }
  }
  
  /* todo: fix the char/string printing formatting.. */

  token_idx = 0;
  for (uint32 i = 0; i < len; i++) {
    if (pattern[i] == '%') {
      uint8 size = is_formatting_argument(pattern[i+1]);
      if (size < 0) {
        // str
      } else if (size > 0) {
        switch (pattern[i+1]) {
          case 'd':
            printd(tokens[token_idx++]);
            break;
          case 'h':
            printh(tokens[token_idx++]);
            break;
          case 'c':
            printch((int8)tokens[token_idx++]);
          default:
            break;
        }
        i += 1; // skip the modifier.
      } else {
        printch(pattern[i]);
      }
    } else {
      printch(pattern[i]);
    }
  }
}

void init_video() {
  set_fg_color(VGA_COLOR_WHITE);
  set_bg_color(VGA_COLOR_BLACK);
  vmem_ptr = (uint16 *)VMEMLOC;
  cls();
}
