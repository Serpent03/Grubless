#pragma once

#include "../sys/common.h"

typedef enum {
  PS2_CW__ = 0
} ps2_control_words;

typedef enum {
  IOPORT_READ_PORT = 0x60,
} io_ports;

typedef enum {
  MODIFIER_LSHIFT = 41,
  MODIFIER_RSHIFT = 53,
  MODIFIER_LCTRL = 29,
  MODIFIER_RCTRL = 0,
  MODIFIER_LALT = 55,
  MODIFIER_RALT = 0,
  MODIFIER_CAPSLOCK = 57
} modifiers;

/*  */
void keyrupt();

/* Return char in buffer */
char get_char();

/* Initialize the PS/2 controller(keyboard + mouse) */
void init_ps2();


