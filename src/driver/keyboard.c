#include "../headers/driver/keyboard.h"
#include "../headers/driver/video.h"
#include "../headers/sys/hal.h"
#include "../headers/util/mem.h"

uint8 c;
bool blocked;
uint8 charmap[256] = {
    0,
    0, /* escape */
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '+',
    '\b', /* backspace */
    '\t', /* tab */
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '[',
    ']',
    '\n', /* enter */
    0,    /* left ctrl */
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ';',
    '\'',
    '`',
    0 /* left shift */,
    '\\',
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    ',',
    '.',
    '/',
    0 /* right shift */,
    '*',
    0 /* left alt */,
    ' ',
    0 /* caps lock */,
    0, /* F1 */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0, /* F10 */
    0, /* numlock */
    0, /* scroll-lock */
    '7', /* numpad */

};

uint8 map[2] = {'5', 1};

void record_keyboard() {
  uint8 key = port_byte_read(IOPORT_READ_PORT);
  c = charmap[key];
  // printd(key);
  // printch(' ');
  // printch(charmap[key]);
  // printch(c);
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
  prints(">>>PS/2 initialized!\n");
}
