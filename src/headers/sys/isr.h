#pragma once

#include "common.h"

typedef struct regs {
  uint32 ds;
  uint32 edi, esi, ebp, _, ebx, edx, ecx, eax;
  uint32 interrupt_id;
  uint32 error_code;
  /* this is pushed automatically during an interrupt. */
  uint32 eip, cs, eflags, esp, ss;
} __attribute__((packed)) regs;

typedef enum {
  INTR_DIV_BY_ZERO = 0,
  INTR_DOUBLE_FAULT = 8,
} interrupts;

/* Interrupt handler stub. Called from assembly with register data REGDATA */
void handle_interrupts(regs *regdata);