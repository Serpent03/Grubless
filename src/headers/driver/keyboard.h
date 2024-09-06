#pragma once

#include "../sys/common.h"

typedef enum {
  PS2_CW__ = 0
} ps2_control_words;

typedef enum {
  IOPORT_READ_PORT = 0x60,
} io_ports;

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
} modifiers;

/*  */
void keyrupt();

/* Return char in buffer */
char get_char();

/* Initialize the PS/2 controller(keyboard + mouse) */
void init_ps2();


