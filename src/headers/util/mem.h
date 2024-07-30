#pragma once

#include "../sys/common.h"

/* Set N bytes of SRC to D. */
void memset(uint8 *src, uint8 d, uint32 n);

/* Copy N bytes of SRC to DST. */
void memcpy(uint8 *dst, uint8 *src, uint32 n);

/* Set N words of SRC to D. */
void memsetw(uint16 *src, uint16 d, uint32 n);

/* Copy N words of SRC to DST. */
void memcpyw(uint16 *dst, uint16 *src, uint32 n);