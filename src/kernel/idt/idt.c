#include "../../headers/sys/idt.h"
#include "../../headers/driver/video.h"
#include "../../headers/util/mem.h"

idt_entry g_IDT_table[256];
idt_descriptor g_IDTDescriptor;

/* corresponding assembly function */
extern void load_idt(idt_descriptor *descriptor);

/* stub ISR functions */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();

void set_idt_entry(uint8 interrupt_id, uint32 addr, uint16 segment_selector,
                   uint8 attributes) {
  g_IDT_table[interrupt_id].addr_high = (addr >> 16) & 0xFFFF;
  g_IDT_table[interrupt_id].addr_low = addr & 0xFFFF;
  g_IDT_table[interrupt_id].segment_selector = segment_selector;
  g_IDT_table[interrupt_id]._zero = 0;
  g_IDT_table[interrupt_id].attributes = attributes;
}

void install_idt() {
  /* Install the IDT through this function. */
  memset((void *)&g_IDT_table, 0, sizeof(idt_entry) * 256);
  g_IDTDescriptor.limit = (sizeof(idt_entry) * 256) - 1;
  g_IDTDescriptor.base = g_IDT_table;
  set_idt_entry(0, (uint32)isr0, 0x8, 0x8E);
  set_idt_entry(1, (uint32)isr1, 0x8, 0x8E);
  set_idt_entry(2, (uint32)isr2, 0x8, 0x8E);
  set_idt_entry(3, (uint32)isr3, 0x8, 0x8E);
  set_idt_entry(4, (uint32)isr4, 0x8, 0x8E);
  set_idt_entry(5, (uint32)isr5, 0x8, 0x8E);
  set_idt_entry(8, (uint32)isr8, 0x8, 0x8E);
}

void init_idt() {
  install_idt();
  load_idt(&g_IDTDescriptor);
  prints(">>IDT installed..\n");
}
