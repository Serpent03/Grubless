#include "../headers/driver/video.h"
#include "../headers/sys/common.h"
#include "../headers/sys/hal.h"
#include "../headers/util/assert.h"
#include "../headers/util/math.h"
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
  x = 0;
  y = 0;
  set_cursor(xyton(0, 0));
}

void scroll(uint16 n) {
  if (n <= 0)
    return;
  uint16 blank = ((uint16)(color) << 8) | ' ';
  for (uint16 i = 0; i < n; i++) {
    uint16 *row = (uint16 *)VMEMLOC;
    for (uint16 j = 0; j < HEIGHT - 1; j++) {
      memcpyw(row, row + WIDTH, WIDTH);
      memsetw(row + WIDTH, blank, WIDTH);
      row += WIDTH;
    }
  }
  x = y - n < 0 ? 0 : x; // if we're clearing the whole screen, reset it
  y = y - n >= 0 ? y - n : 0;
  set_cursor(xyton(x, y));
}

void printch(uint8 c) {
  uint16 vchar = ((uint16)(color) << 8) | c;
  uint16 blank = ((uint16)color << 8) | ' ';
  uint16 cursor;
  bool is_action_char = false;

  switch (c) {
  case '\r': /* return carriage */
    x = 0;
    cursor = xyton(x, y);
    set_cursor(cursor);
    is_action_char = true;
    break;
  case '\n': /* newline */
    x = 0;
    y++;
    cursor = xyton(x, y);
    set_cursor(cursor);
    is_action_char = true;
    break;
  case '\b': /* backspace */
    y = MAX(((x == 0) ? y - 1 : y), 0);
    x = MAX(x - 1, 0);
    /* go back a line if x = 0, otherwise stay here. */
    cursor = xyton(x, y);
    set_cursor(cursor);
    vmem_ptr[cursor] = blank;
    is_action_char = true;
    break;
  default:
    break;
  }

  if (x >= WIDTH) {
    x = 0;
    y++;
  }

  if (y >= HEIGHT) {
    scroll(5);
  }

  cursor = xyton(x, y);
  if (!is_action_char) {
    vmem_ptr[cursor] = vchar;
    x++;
  }
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
  uint32 n = 0;
  uint32 t = d;
  while (t > 0) {
    n++;
    t /= 10;
  }
  if (d == 0) {
    printch('0');
  } else {
    char dec[n];
    uint32 idx = 0;
    while (d > 0) {
      dec[idx++] = d % 10 + '0';
      d /= 10;
    }
    while (idx--) {
      printch(dec[idx]);
    }
  }
}

char itoh(uint8 i) {
  char c;
  if (i >= 0 && i <= 9) {
    c = '0' + i;
  } else if (i >= 10 && i <= 15) {
    c = 'A' + i % 10;
  } else {
    assert(false,
           "out of range element in itoh. make sure you are converting a hex!");
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

/* Get enum for an argument type C. */
uint8 get_arg_type(uint8 c) {
  switch (c) {
  case 'c':
    return ARG_TYPE_CHR;
  case 's':
    return ARG_TYPE_STR;
  case 'x':
    return ARG_TYPE_HEX;
  case 'd':
    return ARG_TYPE_INT;
  case '%':
    return ARG_TYPE_ESC;
  }
  return -1;
}

void printf(char *pattern, ...) {
  /* this function is what K&R meant by blowing your foot off.. */
  void **arg = (void **)(&pattern + 1);
  char *str = pattern;
  bool modifier_encountered = false;

  while (*str) {
    switch (*str) {
    case '%':
      modifier_encountered = true;
      break;
    default:
      printch(*str);
      break;
    }
    if (modifier_encountered) {
      uint8 arg_type = get_arg_type(*(str + 1));
      switch (arg_type) {
      case ARG_TYPE_CHR:
        printch((char)*arg);
        break;
      case ARG_TYPE_STR:
        prints((char *)*arg);
        break;
      case ARG_TYPE_INT:
        printd((int32)*arg);
        break;
      case ARG_TYPE_HEX:
        printh((uint32)*arg);
        break;
      case ARG_TYPE_ESC:
        printch('%');
        break;
      default:
        break;
      }
      arg++;
      str++;
      modifier_encountered = false;
    }
    str++;
  }
}

void init_video() {
  set_fg_color(VGA_COLOR_WHITE);
  set_bg_color(VGA_COLOR_BLACK);
  vmem_ptr = (uint16 *)VMEMLOC;
  cls();
}
