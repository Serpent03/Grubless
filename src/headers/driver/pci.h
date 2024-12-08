#pragma once

#include "../sys/common.h"

#define BUSES 256
#define SLOTS 32
#define FUNCTIONS 8

typedef enum {
  PCI_CONFIG_ADDR_REG = 0xCF8,
  PCI_CONFIG_DATA_REG = 0xCFC
} PCI_REGS;

typedef enum {
  OFFSET_VENDOR_ID = 0x0,
  OFFSET_DEVICE_ID = 0x2,
  OFFSET_COMMAND = 0x4,
  OFFSET_STATUS = 0x6,
  OFFSET_REVISION_ID = 0x8,
  OFFSET_PROG_IF = 0x8,
  OFFSET_SUBCLASS_ID = 0xA,
  OFFSET_CLASS_ID = 0xA,
  OFFSET_CACHE_LINE_SIZE = 0xC,
  OFFSET_LATENCY_TIMER = 0xC,
  OFFSET_HEADER_TYPE = 0xE,
  OFFSET_BIST = 0xE,

} PCI_WORD_OFFSET;

typedef enum {
  MASK_REVISION_ID = ~0xFF00,
  MASK_PROG_IF = ~0x00FF,
  MASK_SUBCLASS_ID = ~0xFF00,
  MASK_CLASS_ID = ~0x00FF,
  MASK_CACHE_LINE_SIZE = ~0xFF00,
  MASK_LATENCY_TIMER = ~0x00FF,
  MASK_HEADER_TYPE = ~0xFF00,
  MASK_BIST = ~0x00FF,
  /* The idea is that when these mask values will be
  inverted, we will have a guarantee of only getting the data
  we want. For example:

  What we want  ↓↓
  Data: 0x12345678
  Mask: 0x    FF00
  What we want  ↑↑

  The compiler may fill in the rest of the empty mask with FF. To ensure
  that we only get the data we want(that being the last byte 0x78), we will zero
  that area and then negate it. It effectively becomes:

  Data: 0x12345678
  Mask: 0x000000FF
  Which allows us to extract 0x78 quite easily.
  */
} PCI_WORD_MASK;

typedef enum {
  /* These are all the relevant offsets for
  PCI header type 0 */
  OFFSET_PCI0_BAR0 = 0x10,
  OFFSET_PCI0_BAR1 = 0x14,
  OFFSET_PCI0_BAR2 = 0x18,
  OFFSET_PCI0_BAR3 = 0x1C,
  OFFSET_PCI0_BAR4 = 0x20,
  OFFSET_PCI0_BAR5 = 0x24,
  OFFSET_PCI0_CISPTR0 = 0x28,
  OFFSET_PCI0_CISPTR1 = 0x2A,
  OFFSET_PCI0_SUBSYS_VENDOR_ID = 0x2C,
  OFFSET_PCI0_SUBSYS_ID = 0x2E,
  OFFSET_PCI0_ROM_BAR = 0x30,
  OFFSET_PCI0_CAPABILITIES_PTR = 0x34,
  OFFSET_PCI0_INTR_LINE = 0x3C,
  OFFSET_PCI0_INTR_PIN = 0x3C,
  OFFSET_PCI0_MIN_GRANT = 0x3E,
  OFFSET_PCI0_MAX_LATENCY = 0x3E
} PCI0_WORD_OFFSET;

typedef enum {
  MASK_PCI_BAR_IO = ~0x3,
  MASK_PCI_BAR_MMIO = ~0xF,
  MASK_PCI0_CAPABILITIES_PTR = ~0xFF00,
  MASK_PCI0_INTR_LINE = ~0xFF00,
  MASK_PCI0_INTR_PIN = ~0x00FF,
  MASK_PCI0_MIN_GRANT = ~0xFF00,
  MASK_PCI0_MAX_LATENCY = ~0x00FF,
} PCI0_WORD_MASK;

typedef struct __pci_device_id {
  uint16 bus;
  uint16 slot;
  uint16 function;
} pci_device_id;

typedef struct __pci_device {
  uint16 vendor_id;
  uint16 device_id;
  uint16 class_id;
  uint16 subclass_id;
  struct __pci_device_id *table;
} pci_device;

/* Initialize the PCI bus. */
void init_pci();
