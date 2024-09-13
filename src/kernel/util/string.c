#include "../../headers/util/string.h"

uint32 strlen(int8 *s) {
  uint32 i = 0;
  while (s[++i]) {
  }
  return i;
}

bool is_upper(char c) { return is_alnum(c) && c >= 'A' && c <= 'Z'; }

bool is_lower(char c) { return is_alnum(c) && c >= 'a' && c <= 'z'; }

bool is_alnum(char c) {
  return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
         (c >= 'a' && c <= 'z');
}

char toggle_case(char c) {
  if (!is_alnum(c))
    return c;
  char d = 0;
  if (is_upper(c)) {
    d = c + 0x20;
  } else if (is_lower(c)) {
    d = c - 0x20;
  }
  return d;
}