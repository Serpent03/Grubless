#include "../../headers/util/mem.h"

void memset(uint8 *src, uint8 d, uint32 n) {
  while (n--) {
    src[n] = d;
  }
}

/* Copy N bytes of SRC to DST. */
void memcpy(uint8 *dst, uint8 *src, uint32 n) {
  uint32 m = n;
  uint8 buf[n];
  /* This should ensure that we don't end up
  having trouble where the address are close-by. */
  while (m--)
    buf[n] = src[m];
  while (n--)
    dst[n] = buf[n];
}

/* Set N words of SRC to D. */
void memsetw(uint16 *src, uint16 d, uint32 n) {
  while (n--) {
    src[n] = d;
  }
}

/* Copy N words of SRC to DST. */
void memcpyw(uint16 *dst, uint16 *src, uint32 n) {
  uint32 m = n;
  uint16 buf[n];
  while (m--)
    buf[m] = src[m];
  while (n--) 
    dst[n] = buf[n];
  
}