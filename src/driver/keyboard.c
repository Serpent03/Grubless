#include "../headers/driver/keyboard.h"
#include "../headers/driver/video.h"
#include "../headers/sys/hal.h"
#include "../headers/util/string.h"
#include "../headers/util/mem.h"

char c;
bool blocked;
uint8 modifier_flags;
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
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '\n', /* enter */
    0,    /* left ctrl */
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '`',
    0 /* left shift */,
    '\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
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
    0,   /* F10 */
    0,   /* numlock */
    0,   /* scroll-lock */
    '7', /* numpad */
    '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    '2',
    '3',
    '0',
    '.',
    0,
    0,
    0,
    0 /* F11 */,
    0 /* F12 */
};

char shifted_charmap[256];

void toggle_shift() {
  /* since caps lock and shift both modify this behavior
  we can simply toggle it away */
  if (modifier_flags & 0x1) {
    modifier_flags &= ~0x1;
  } else {
    modifier_flags |= 0x1;
  }
}

void enable_ctrl() { modifier_flags |= 0x2; }

void enable_alt() { modifier_flags |= 0x4; }

void disable_ctrl() { modifier_flags &= ~(0x2); }

void disable_alt() { modifier_flags &= ~(0x4); }

bool is_shift_held() { return modifier_flags & 0x1; }

bool is_ctrl_held() { return modifier_flags & 0x2; }

bool is_alt_held() { return modifier_flags & 0x4; }

void keyrupt() {
  uint8 key = port_byte_read(IOPORT_READ_PORT);
  c = charmap[key];
  // printf("%x :: %x\n", c, key);
  /* other logic for trigger modifier keys */
  if (key == MODIFIER_LSHIFT_PRESS || key == MODIFIER_RSHIFT_PRESS ||
      key == MODIFIER_CAPSLOCK_PRESS || key == MODIFIER_LSHIFT_REL ||
      key == MODIFIER_RSHIFT_REL) {
    toggle_shift();
  }

  if (key == MODIFIER_LCTRL_PRESS || key == MODIFIER_RCTRL_PRESS) {
    enable_ctrl();
  } else if (key == MODIFIER_LCTRL_REL || key == MODIFIER_RCTRL_REL) {
    disable_ctrl();
  }
  if (key == MODIFIER_LALT_PRESS || key == MODIFIER_RALT_PRESS) {
    enable_alt();
  } else if (key == MODIFIER_LALT_REL || key == MODIFIER_RALT_REL) {
    disable_alt();
  }

  /* this is going to need rework. for now it should handle
  base cases */
  // printd(is_shift_held());
  if (is_shift_held()) {
    c = toggle_case(c);
  }
  if (is_ctrl_held()) {
  }
  if (is_alt_held()) {
  }
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
  modifier_flags = 0;
  prints(">>>PS/2 initialized!\n");
}
