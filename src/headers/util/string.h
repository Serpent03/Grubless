#pragma once

#include "../sys/common.h"

/* Returns the length of string S. */
uint32 strlen(int8 *s);

/* Returns true if char C is uppercase and alphanum. */
bool is_upper(char c);

/* Returns true is char C is lowercase and alphanum. */
bool is_lower(char c);

/* Returns true if char C is alphanumeric. */
bool is_alnum(char c);

/* Returns uppercase if char C is lowercase, else lowercase. */
char toggle_case(char c);
