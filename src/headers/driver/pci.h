#pragma once

#include "../sys/common.h"

typedef enum {
  PCI_CONFIG_ADDR_REG = 0xCF8,
  PCI_CONFIG_DATA_REG = 0xCFC
} PCI_REGS;


/* Initialize the PCI bus. */
void init_pci();
