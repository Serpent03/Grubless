#include "../headers/sys/hal.h"

uint8 port_byte_read(uint16 P) {
  uint8 result;
  __asm__("in %%dx, %%al" : "=a"(result) : "d"(P));
  return result;
}

void port_byte_write(uint16 P, uint8 N) {
  __asm__("out %%al, %%dx" ::"a"(N), "d"(P));
}

uint16 port_word_read(uint16 P) {
  uint16 result;
  __asm__("in %%dx, %%ax" : "=a"(result) : "d"(P));
  return result;
}

uint32 port_dword_read(uint16 P) {
  uint32 result;
  __asm__("in %%dx, %%eax" : "=a"(result) : "d"(P));
  return result;
}

void port_word_write(uint16 P, uint16 N) {
  __asm__("out %%ax, %%dx" ::"a"(N), "d"(P));
}

void port_dword_write(uint16 P, uint32 N) {
  __asm__("out %%eax, %%dx" ::"a"(N), "d"(P));
}

void io_wait() { port_byte_write(0x80, 0); }