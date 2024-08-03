#include "../headers/sys/systimer.h"
#include "../headers/sys/hal.h"

/*
  sys_tick: PIT counter. When sys_tick % sys_freq == 0, a second has passed.
  sys_freq: PIT interrupts  per second
  sys_time: actual CPU uptime
*/
uint32 sys_tick;
uint64 sys_time; /* milliseconds */
uint16 sys_freq;

void init_systime() {
  sys_time = 0;
  sys_tick = 0;
  sys_freq = 18; /* default */
}

void set_pit_tick_phase(uint16 freq) {
  if (freq < LOWEST_POSSIBLE_FREQ) {
    freq = (uint16)LOWEST_POSSIBLE_FREQ;
  } else if (freq > OSCILLATOR_FREQ) {
    freq = (uint16)OSCILLATOR_FREQ;
  }
  uint16 div = OSCILLATOR_FREQ / freq;

  /* counter 0, read-write square wave mode */
  port_byte_write(PIT_CMND_REG, 0x36);
  port_byte_write(PIT1_DATA_REG, div & 0xFF);
  port_byte_write(PIT1_DATA_REG, (div >> 8) & 0xFF);

  sys_tick = 0;
  sys_freq = freq;
}

void pit_tick() {
  sys_tick++;
  sys_time += (DEFAULT_PIT_PRECISION / sys_freq);
}

uint64 get_time() { return sys_time; }

void sleep(uint64 ms) {
  uint64 ref_time = sys_time;
  while (ref_time + ms >= sys_time) {
    continue;
  }
}

void init_sysclock() {
  init_systime();
  set_pit_tick_phase(DEFAULT_PIT_PRECISION); /* intercept PIT every 0.001ms */
}
