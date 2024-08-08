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
  INTR_DIV_BY_ZERO =                     0,
  INTR_SINGLE_STEP_INTERRUPT =           1,
  INTR_NON_MASKABLE_INTERRUPT =          2,
  INTR_BREAKPOINT =                      3,
  INTR_OVERFLOW =                        4,
  INTR_BOUND_RANGE_EXCEEDED =            5,
  INTR_INVALID_OPCODE =                  6,
  INTR_COPROCESSOR_NOT_AVAILABLE =       7,
  INTR_DOUBLE_FAULT =                    8,
  INTR_COPROCESSOR_SEGMENT_OVERRUN =     9,
  INTR_INVALID_TASK_STATE_SEGMENT =     10,
  INTR_SEGMENT_NOT_PRESENT =            11,
  INTR_STACK_SEGMENT_FAULT =            12,
  INTR_GENERAL_PROTECTION_FAULT =       13,
  INTR_PAGE_FAULT =                     14,

  INTR_FLOATING_POINT_EXCEPTION =       16,
  INTR_ALIGNMENT_CHECK =                17,
  INTR_MACHINE_CHECK =                  18,
  INTR_SIMD_FLOATING_POINT_EXCEPTION =  19,
  INTR_VIRTUALIZATION_EXCEPTION =       20,
  INTR_CONTROL_PROTECTION_EXCEPTION =   21,
} interrupts;

/* Interrupt handler stub. Called from assembly with register data REGDATA */
void handle_interrupts(regs *regdata);