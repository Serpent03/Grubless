#pragma once

#include "../sys/common.h"

/* Fail with value STR if EXPR is false. */
void assert(bool expr, char *str);