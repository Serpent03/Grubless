#include "../../headers/driver/pci.h"
#include "../../headers/driver/video.h"
#include "../../headers/sys/hal.h"

uint16 dev;
pci_device pci_device_t[256];

uint16 read_pci_word(uint16 bus, uint16 slot, uint16 func, uint16 offset) {
  /* read the config address(PCI_CONFIG_ADDR_REG) which contains
  details on vendor, device and other miscellaneous items.

  The flow for probe goes as follows:
  - write to 0xCF8(ADDR_REG)
  - read from 0xCFC(DATA_REG)
  */

  uint64 qw_bus = (uint64)bus;
  uint64 qw_slot = (uint64)slot;
  uint64 qw_func = (uint64)func;
  uint64 qw_offset = (uint64)offset;
  uint64 address = (uint64)((qw_bus << 16) | (qw_slot << 11) | (qw_func) << 8 |
                            (qw_offset & 0xFC) | (uint32)(0x80000000));

  port_dword_write(PCI_CONFIG_ADDR_REG, address);
  uint16 ret_value =
      (uint16)(port_dword_read(PCI_CONFIG_DATA_REG) >> ((offset & 2) * 8) &
               0xFFFF);
  return ret_value;
}

void write_pci_word(uint16 bus, uint16 slot, uint16 function, uint16 offset,
                    uint16 data) {
  uint64 qw_bus = (uint64)bus;
  uint64 qw_slot = (uint64)slot;
  uint64 qw_func = (uint64)function;
  uint64 qw_offset = (uint64)offset;
  uint64 address = (uint64)((qw_bus << 16) | (qw_slot << 11) | (qw_func) << 8 |
                            (qw_offset & 0xFC) | (uint32)(0x80000000));

  port_dword_write(PCI_CONFIG_ADDR_REG,
                   address); /* we select the device to write to. */
  uint16 data_port = (PCI_CONFIG_DATA_REG + offset) & 0x2;
  port_word_write(data_port, data);
}

uint16 get_vendor_id(uint16 bus, uint16 slot, uint16 function) {
  uint16 r0 = read_pci_word(bus, slot, function, OFFSET_VENDOR_ID);
  return r0;
}

uint16 get_device_id(uint16 bus, uint16 slot, uint16 function) {
  uint16 r0 = read_pci_word(bus, slot, function, OFFSET_DEVICE_ID);
  return r0;
}

uint16 get_class_id(uint16 bus, uint16 slot, uint16 function) {
  uint16 r0 = read_pci_word(bus, slot, function, OFFSET_CLASS_ID);
  return (r0 & ~MASK_CLASS_ID) >> 8;
}

uint16 get_subclass_id(uint16 bus, uint16 slot, uint16 function) {
  uint16 r0 = read_pci_word(bus, slot, function, OFFSET_SUBCLASS_ID);
  return (r0 & ~MASK_SUBCLASS_ID);
}

uint16 get_header_type(uint16 bus, uint16 slot, uint16 function) {
  uint16 r0 = read_pci_word(bus, slot, function, OFFSET_HEADER_TYPE);
  return (r0 & ~MASK_HEADER_TYPE);
}

uint32 get_bar_address(uint16 bus, uint16 slot, uint16 function,
                       uint8 bar_offset) {
  /* return n-th BAR value from given offset */
  uint32 bar_address, return_address;
  uint32 r0 = read_pci_word(bus, slot, function, bar_offset);
  uint32 r1 = read_pci_word(bus, slot, function, bar_offset + 0x2);
  return_address = (r1 << 16) | r0;
  if (return_address & 0x1) {
    /* MMIO */
    bar_address = return_address & ~MASK_PCI_BAR_MMIO;
  } else {
    /* I/O mapped */
    bar_address = return_address & ~MASK_PCI_BAR_IO;
  }
  return bar_address;
}

void probe_pci() {
  /* At bootup, we have no idea of what devices are connected,
  and what configuration/addresses they have taken through PCI; thus
  we must query it all:
  - 256 buses
  - 32 slots per bus
  - 8 functions per slot

  - Store all devices by VENDOR, DEVICE, CLASS and SUBCLAS ID.
  - Write ATA/IDE drivers through the PCI. Use the PROG-IF to
  ensure that they are in PCI mode, and then access through
  the BARs.

  EDIT: all Intel devices have the vendor ID 0x8086.. har har
   */
  for (uint16 bus_idx = 0; bus_idx < BUSES; bus_idx++) {
    for (uint16 slot_idx = 0; slot_idx < SLOTS; slot_idx++) {
      for (uint16 func_idx = 0; func_idx < FUNCTIONS; func_idx++) {
        uint16 vendor = get_vendor_id(bus_idx, slot_idx, func_idx);
        if (vendor == 0xFFFF) {
          /* 0xFFFF is not a valid address. */
          continue;
        }
        uint16 device = get_device_id(bus_idx, slot_idx, func_idx);
        uint16 header = get_header_type(bus_idx, slot_idx, func_idx);
        uint16 class = get_class_id(bus_idx, slot_idx, func_idx);
        uint16 subclass = get_subclass_id(bus_idx, slot_idx, func_idx);
        printf("VNDR: 0x%x, DEV: 0x%x, HDR: 0x%x, Cl: 0x%x, SubCl: 0x%x\n",
               vendor, device, header, class, subclass);
        /* Add PCI devices in a logical manner */
        uint32 bar0 =
            get_bar_address(bus_idx, slot_idx, func_idx, OFFSET_PCI0_BAR0);
      }
    }
  }
}

void install_pci() {
  /* configure the PCI bus. One of the first things that need to be
  done is to get ATA/IDE port data. */
  dev = 0;
  probe_pci();
}

void init_pci() {
  install_pci();
  printf(">>>PCI installed.\n");
}
