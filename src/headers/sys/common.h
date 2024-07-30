#pragma once

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short int uint16;
typedef short int int16;
typedef unsigned int uint32;
typedef int int32;

/* Read data(u8) from a port P. */
uint8 port_byte_read(uint16 P);

/* Write data N to a port P. */
void port_byte_write(uint16 P, uint8 N);

/* Read data(u16) from a port P. */
uint16 port_word_read(uint16 P);

/* Write data N to a port P. */
void port_word_write(uint16 P, uint16 N);