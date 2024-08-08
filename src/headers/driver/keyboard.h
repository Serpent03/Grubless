#pragma once

#include "../sys/common.h"

typedef enum {
  IOPORT_READ_PORT = 0x60,
} io_ports;

/*  */
void record_keyboard();

/* Return char in buffer */
int8 get_char();

/* Initialize the PS/2 controller(keyboard + mouse) */
void init_ps2();


