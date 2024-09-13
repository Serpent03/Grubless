#include "../headers/driver/keyboard.h"
#include "../headers/driver/video.h"
#include "../headers/sys/hal.h"
#include "../headers/util/mem.h"
#include "../headers/util/string.h"

char c;
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

char shifted_charmap[256] = {0};

int32 front;
int32 rear;
char keyb_buffer[KEY_BUFFER_SIZE];

void toggle_shift() {
  /* since caps lock and shift both modify this behavior
  we can simply toggle it away */
  if (modifier_flags & MODIFIER_BITFLAG_SHIFT) {
    modifier_flags &= ~MODIFIER_BITFLAG_SHIFT;
  } else {
    modifier_flags |= MODIFIER_BITFLAG_SHIFT;
  }
}

void enable_ctrl() { modifier_flags |= MODIFIER_BITFLAG_CTRL; }

void enable_alt() { modifier_flags |= MODIFIER_BITFLAG_ALT; }

void disable_ctrl() { modifier_flags &= ~(MODIFIER_BITFLAG_CTRL); }

void disable_alt() { modifier_flags &= ~(MODIFIER_BITFLAG_ALT); }

bool is_shift_held() { return modifier_flags & MODIFIER_BITFLAG_SHIFT; }

bool is_ctrl_held() { return modifier_flags & MODIFIER_BITFLAG_CTRL; }

bool is_alt_held() { return modifier_flags & MODIFIER_BITFLAG_ALT; }

void add_char_to_keyb_buffer(char c) {
  if (rear == -1 && front == rear) {
    /* If buffer is empty */
    rear = 0;
    front = 0;
  } else if (rear == front) {
    front = (front + 1) % KEY_BUFFER_SIZE;
  }
  keyb_buffer[rear] = c;
  rear = (rear + 1) % KEY_BUFFER_SIZE;
}

char get_char_from_keyb_buffer() {
  /* This ensures that it will block until
  the buffer is atleast one character wide. */
  while (rear == -1) {
  }
  char c;
  c = keyb_buffer[front];
  if (front == rear) {
    /* If only one character remains, return that
    and set the ring buffer to be empty. */
    front = -1;
    rear = -1;
  } else {
    front = (front + 1) % KEY_BUFFER_SIZE;
  }
  return c;
}

void flush_keyb_buffer() {
  front = -1;
  rear = -1;
}

void keyrupt() {
  uint8 key = port_byte_read(IOPORT_READ_PORT);
  c = charmap[key];
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
  if (is_shift_held()) {
    c = toggle_case(c);
  }
  if (is_ctrl_held()) {
  }
  if (is_alt_held()) {
  }

  if (c > 0) {
    /* temporary measure until I implement
    key rel */
    add_char_to_keyb_buffer(c);
  }
}

char get_char() {
  char c = get_char_from_keyb_buffer();
  while (c == 0) {
    /* @fix: for some reason it returns a 0 on key release
    from the get_char() function.  */
    c = get_char_from_keyb_buffer();
  }
  return c;
}

void install_ps2() {}

void init_ps2() {
  install_ps2();
  flush_keyb_buffer();
  c = 0;
  modifier_flags = 0;
  prints(">>>PS/2 initialized!\n");
}
