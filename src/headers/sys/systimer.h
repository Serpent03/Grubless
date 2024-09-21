#pragma once

#include "common.h"

#define OSCILLATOR_FREQ 1193180 /* default tick in Hz */
#define LOWEST_POSSIBLE_FREQ 18
#define DEFAULT_PIT_PRECISION 20 /* milliseconds */
/* @fix: it seems like using PIT precision to fire every 18 milliseconds
bugs it out. Fixing it at 19 milliseconds restores intended behavior. Not sure
why. Currently set to fire every 20 milliseconds for the sake of consistency. */

#define PIT_CMND_REG 0x43
#define PIT1_DATA_REG 0x40
#define PIT2_DATA_REG 0x41
#define PIT3_DATA_REG 0x42

/* Zero the current system up-time. */
void init_systime();

/* Fire the clock tick from IRQ0 FREQ times in a second Lowest value is 18Hz,
 * highest 1.19MHz. */
void set_pit_tick_phase(uint16 freq);

/* PIT interrupt calls this function. */
void pit_tick();

/* Return current system time in milliseconds. */
uint64 get_time();

/* Return current system time in seconds. */
uint64 get_time_s();

/* Delay the current thread for MS milliseconds. */
void sleep(uint64 ms);

/* Delay the current thread for S seconds. */
void sleep_s(uint64 s);

/* Initialize the system clock and set PIT frequency. */
void init_sysclock();
