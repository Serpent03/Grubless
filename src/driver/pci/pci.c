#include "../../headers/driver/pci.h"
#include "../../headers/sys/hal.h"

void install_pci() {
  /* configure the PCI bus. One of the first things that need to be
  done is to get ATA/IDE port data. */
}



void init_pci() {
  install_pci();
  printf(">>>PCI installed.\n");
}
