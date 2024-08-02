#include "../../headers/util/assert.h"
#include "../../headers/driver/video.h"

void assert(bool expr, char *str) {
  /* for current purposes, just hang with a while loop. */
  if (!expr) {
    prints("\nASSERT FAILED: ");
    prints(str);
  repeat:
    goto repeat;
  }
}