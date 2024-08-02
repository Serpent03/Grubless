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
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();

/* stub IRQ functions */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

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

  /* Reserved CPU interrupts/traps */
  set_idt_entry(0, (uint32)isr0, 0x8, 0x8E);
  set_idt_entry(1, (uint32)isr1, 0x8, 0x8E);
  set_idt_entry(2, (uint32)isr2, 0x8, 0x8E);
  set_idt_entry(3, (uint32)isr3, 0x8, 0x8E);
  set_idt_entry(4, (uint32)isr4, 0x8, 0x8E);
  set_idt_entry(5, (uint32)isr5, 0x8, 0x8E);
  set_idt_entry(6, (uint32)isr6, 0x8, 0x8E);
  set_idt_entry(7, (uint32)isr7, 0x8, 0x8E);
  set_idt_entry(9, (uint32)isr8, 0x8, 0x8E);
  set_idt_entry(9, (uint32)isr9, 0x8, 0x8E);
  set_idt_entry(15, (uint32)isr15, 0x8, 0x8E);

  /* these are where we remap the PIC interrupts to. */
  set_idt_entry(32, (uint32)irq0, 0x8, 0x8E);
  set_idt_entry(33, (uint32)irq1, 0x8, 0x8E);
  set_idt_entry(34, (uint32)irq2, 0x8, 0x8E);
  set_idt_entry(35, (uint32)irq3, 0x8, 0x8E);
  set_idt_entry(36, (uint32)irq4, 0x8, 0x8E);
  set_idt_entry(37, (uint32)irq5, 0x8, 0x8E);
  set_idt_entry(38, (uint32)irq6, 0x8, 0x8E);
  set_idt_entry(39, (uint32)irq7, 0x8, 0x8E);
  set_idt_entry(40, (uint32)irq8, 0x8, 0x8E);
  set_idt_entry(41, (uint32)irq9, 0x8, 0x8E);
  set_idt_entry(42, (uint32)irq10, 0x8, 0x8E);
  set_idt_entry(43, (uint32)irq11, 0x8, 0x8E);
  set_idt_entry(44, (uint32)irq12, 0x8, 0x8E);
  set_idt_entry(45, (uint32)irq13, 0x8, 0x8E);
  set_idt_entry(46, (uint32)irq14, 0x8, 0x8E);
  set_idt_entry(47, (uint32)irq15, 0x8, 0x8E);
}

void init_idt() {
  install_idt();
  load_idt(&g_IDTDescriptor);
  prints(">>IDT installed..\n");
}
