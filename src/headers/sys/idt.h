#pragma once

#include "common.h"

typedef struct idt_entry {
  uint16 addr_low;
  uint16 segment_selector;
  uint8 _zero; /* this exists without use. */
  uint8 attributes;
  uint16 addr_high;
} __attribute__((packed)) idt_entry;
/* attribute packed ensures that the compiler does not pad this structure. */

typedef struct idt_descriptor {
  uint16 limit;
  idt_entry *base;
} __attribute__((packed)) idt_descriptor;

typedef enum {
  IDT_FLAG_GATE_TASK = 0x5,
  /* task gate is used for TSS(task segment switch). In use with context
     switches. */
  IDT_FLAG_GATE_16BIT_INTR = 0x6,
  IDT_FLAG_GATE_16BIT_TRAP = 0x7,
  IDT_FLAG_GATE_32BIT_INTR = 0xE,
  IDT_FLAG_GATE_32BIT_TRAP = 0xF,

  IDT_FLAG_RING0 = (0 << 5),
  IDT_FLAG_RING1 = (1 << 5),
  IDT_FLAG_RING2 = (2 << 5),
  IDT_FLAG_RING3 = (3 << 5),

  IDT_FLAG_PRESENT = 0x80,
} idt_flags;

/* Install the IDT. */
void init_idt();

/*
  Sets am interrupt vector INTERRUPT_ID, with calling address ADDR, and segment
  seelector SEGMENT_SELECTOR, and ATTRIBUTES as flags.
 */
void set_idt_entry(uint8 interrupt_id, uint32 addr, uint16 segment_selector,
                   uint8 attributes);
