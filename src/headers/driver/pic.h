#pragma once

#include "../sys/common.h"
#include "../sys/isr.h"

#define PIC_MTR_CMND_REG 0x0020
#define PIC_MTR_DATA_REG 0x0021
#define PIC_SLV_CMND_REG 0x00A0
#define PIC_SLV_DATA_REG 0x00A1

#define PIC_MTR_OFFSET 0x20
#define PIC_SLV_OFFSET 0x28
/*
  In effect: 
  PIC master will remap from 0x20 .. 0x20 + 7
  PIC slave will remap to 0x28 .. 0x28 + 7
  
  This exactly checks out with what we installed in
  kernel/idt/idt.c, placing iqr0 .. irq15 to these addresses.
*/

typedef enum {
  PIC_COMMAND_ICW4 = 0x01,
  PIC_COMMAND_INIT = 0x10,
  PIC_COMMAND_EOI = 0x20 /* end of instruction */
} pic_commands;

typedef enum {
  PIC_FLAG_IC4W_8086 = 0x1,
} pic_flags;

typedef enum {
  PIC_INTERRUPT_PIT = 0x0,
  PIC_INTERRUPT_KEYBOARD = 0x1
} pic_interrupts;

/* Enable and remap the PICs. */
void init_pic();

/* Interrupt request handler stub. Called from assembly with register data
 * REGDATA */
void irq_handler(regs *regdata);
