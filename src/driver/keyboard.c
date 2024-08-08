#include "../headers/driver/keyboard.h"
#include "../headers/sys/hal.h"
#include "../headers/driver/video.h"
#include "../headers/util/mem.h"

int8 c;
bool blocked;
int8 charmap[256] = {
    1, /* escape */
    '1',  '2', '3', '4', '5', '6',  '7',
    '8',  '9', '0', '-', '+', '\b', /* backspace */
    '\t',                           /* tab */
    'Q',  'W', 'E', 'R', 'T', 'Y',  'U',
    'I',  'O', 'P', '[', ']', '\n', /* enter */
    0,                              /* left ctrl */
};

void record_keyboard() {
  uint8 key = port_byte_read(IOPORT_READ_PORT);
  c = charmap[key];
  // printd(key);
  // printch(' ');
  // printch(charmap[key]);
  // printd(c);
  // printch('\n');
  blocked = (c == 0) ? true : false;
}

int8 get_char() {
  while (blocked) {
  }
  blocked = true;
  return c;
}

void install_ps2() {}

void init_ps2() {
  install_ps2();
  c = 0;
  blocked = true;
  memset((uint8*)charmap, '1', 256);
  prints(">>>PS/2 initialized!\n");
}
