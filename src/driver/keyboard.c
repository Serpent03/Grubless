#include "../headers/driver/keyboard.h"
#include "../headers/driver/video.h"
#include "../headers/sys/hal.h"
#include "../headers/util/mem.h"

char c;
bool blocked;
char charmap[256] = {
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
    '\n',           /* enter */
    MODIFIER_LCTRL, /* left ctrl */
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
    MODIFIER_LSHIFT /* left shift */,
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
    MODIFIER_RSHIFT /* right shift */,
    '*',
    MODIFIER_LALT /* left alt */,
    ' ',
    MODIFIER_CAPSLOCK /* caps lock */,
    0, /* F1 */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,   /* F10 */
    0,   /* numlock */
    0,   /* scroll-lock */
    '7', /* numpad */

};

char shifted_charmap[128];

void keyrupt() {
  char key = port_byte_read(IOPORT_READ_PORT);
  c = charmap[key];
  /* other logic for trigger modifier keys */
  blocked = (c == 0) ? true : false;
}

char get_char() {
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
