#pragma once

#include "../sys/common.h"

#define KEY_BUFFER_SIZE 256

typedef enum { PS2_CW__ = 0 } ps2_control_words;

typedef enum {
  IOPORT_READ_PORT = 0x60,
} io_port_commands;

typedef enum {
  MODIFIER_LSHIFT_PRESS = 0x2A,
  MODIFIER_RSHIFT_PRESS = 0x36,
  MODIFIER_LCTRL_PRESS = 0x1D,
  MODIFIER_RCTRL_PRESS = 0,
  MODIFIER_LALT_PRESS = 0x38,
  MODIFIER_RALT_PRESS = 0,
  MODIFIER_CAPSLOCK_PRESS = 0x3A,

  MODIFIER_LSHIFT_REL = 0xAA,
  MODIFIER_RSHIFT_REL = 0xB6,
  MODIFIER_LCTRL_REL = 0x9D,
  MODIFIER_RCTRL_REL = 0,
  MODIFIER_LALT_REL = 0xB8,
  MODIFIER_RALT_REL = 0,
  MODIFIER_CAPSLOCK_REL = 0xBA
} modifiers_index;

typedef enum {
  MODIFIER_BITFLAG_SHIFT = 0x1,
  MODIFIER_BITFLAG_CTRL = 0x2,
  MODIFIER_BITFLAG_ALT = 0x4,
} modifier_bitflag;

/* Callback function on IRQ interrupt for keyboard. */
void keyrupt();

/* Return char in buffer */
char get_char();

/* Initialize the PS/2 controller(keyboard + mouse) */
void init_ps2();
