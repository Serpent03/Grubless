#include "../../headers/driver/pic.h"
#include "../../headers/driver/video.h"
#include "../../headers/sys/hal.h"

void irq_handler(regs *regdata) {
  if (regdata->interrupt_id == PIC_INTERRUPT_PIT) {
    port_byte_write(PIC_MTR_CMND_REG, PIC_COMMAND_EOI);
    return;
  }

  switch (regdata->interrupt_id) {
  case PIC_INTERRUPT_KEYBOARD:
    /* dispatch to the keyboard driver */
    uint8 key = port_byte_read(0x60);
    printch((int8)key);
  default:
    port_byte_write(PIC_MTR_CMND_REG, PIC_COMMAND_EOI);
    port_byte_write(PIC_SLV_CMND_REG, PIC_COMMAND_EOI);
  }
  if (regdata->interrupt_id == 0) {
    port_byte_write(PIC_MTR_CMND_REG, PIC_COMMAND_EOI);
    return;
  }
}

void install_pic() {
  uint8 mask_master, mask_slave;

  mask_master = port_byte_read(PIC_MTR_DATA_REG);
  mask_slave = port_byte_read(PIC_SLV_DATA_REG);

  /* not sure if the io_wait() calls are necessary if I am alternating between
   * the two data registers. */

  port_byte_write(PIC_MTR_CMND_REG, PIC_COMMAND_INIT | PIC_COMMAND_ICW4);
  io_wait();
  port_byte_write(PIC_SLV_CMND_REG, PIC_COMMAND_INIT | PIC_COMMAND_ICW4);
  io_wait();

  port_byte_write(PIC_MTR_DATA_REG, PIC_MTR_OFFSET);
  io_wait();
  port_byte_write(PIC_SLV_DATA_REG, PIC_SLV_OFFSET);
  io_wait();

  port_byte_write(PIC_MTR_DATA_REG, 0x4);
  io_wait();
  port_byte_write(PIC_SLV_DATA_REG, 0x2);
  io_wait();

  port_byte_write(PIC_MTR_DATA_REG, PIC_FLAG_IC4W_8086);
  io_wait();
  port_byte_write(PIC_SLV_DATA_REG, PIC_FLAG_IC4W_8086);
  io_wait();

  // port_byte_write(PIC_MTR_DATA_REG, mask_master);
  // port_byte_write(PIC_SLV_DATA_REG, mask_slave);
}

void init_pic() {
  install_pic();
  asm volatile("sti");
  prints(">>PIC installed...\n");
}