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
  OFFSET_CLASS_ID = 0xA,
  OFFSET_SUBCLASS_ID = 0xA
} PCI_WORD_OFFSET;

typedef enum {
  MASK_CLASS_ID = 0x00FF,
  MASK_SUBCLASS_ID = 0xFF00
} PCI_WORD_MASK;

/* Initialize the PCI bus. */
void init_pci();
