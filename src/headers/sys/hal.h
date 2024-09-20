#pragma once

#include "./common.h"

/* Read data(u8) from a port P. */
uint8 port_byte_read(uint16 P);

/* Write data N(u8) to a port P. */
void port_byte_write(uint16 P, uint8 N);

/* Read data(u16) from a port P. */
uint16 port_word_read(uint16 P);

/* Write data N(u16)to a port P. */
void port_word_write(uint16 P, uint16 N);

/* Read data(u32) from a port P. */
uint32 port_dword_read(uint16 P);

/* Write data N(u32) to a port P. */
void port_dword_write(uint32 P, uint16 N);

/* A simple and imprecise delay inductor. Use as less as possible. */
void io_wait();