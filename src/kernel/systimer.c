#include "../headers/sys/systimer.h"
#include "../headers/sys/hal.h"

uint64 sys_timer;
uint16 freq;

void init_systime() {
  sys_timer = 0;
  freq = 18; /* default */
}

void set_systime_tick_phase(uint16 freq) {
  int32 div = OSCILLATOR_FREQ / freq;
  div = (div >= LOWEST_POSSIBLE_FREQ) ? div : LOWEST_POSSIBLE_FREQ;
  div = (div <= OSCILLATOR_FREQ) ? div : OSCILLATOR_FREQ;

  /* counter 0, read-write square wave mode */
  port_byte_write(PIT_CMND_REG, 0x36);
  port_byte_write(PIT1_DATA_REG, div & 0xFF);
  port_byte_write(PIT1_DATA_REG, (div >> 8) & 0xFF);
}



