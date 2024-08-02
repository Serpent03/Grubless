#include "../../headers/util/mem.h"

void memset(uint8 *src, uint8 d, uint32 n) {
  while (n--) {
    src[n] = d;
  }
}

/* Copy N bytes of SRC to DST. */
void memcpy(uint8 *dst, uint8 *src, uint32 n) {
  while (n--) {
    dst[n] = src[n];
  }
}

/* Set N words of SRC to D. */
void memsetw(uint16 *src, uint16 d, uint32 n) {
  while (n--) {
    src[n] = d;
  }
}

/* Copy N words of SRC to DST. */
void memcpyw(uint16 *dst, uint16 *src, uint32 n) {
  while (n--) {
    dst[n] = src[n];
  }
}