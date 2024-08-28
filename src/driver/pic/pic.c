#include "../../headers/driver/pic.h"
#include "../../headers/driver/video.h"
#include "../../headers/driver/keyboard.h"
#include "../../headers/sys/hal.h"
#include "../../headers/sys/systimer.h"

/**
 * Below is the IRQ handling diagram for clarity.

 *                                      TO CPU
 *                                         ▲
 *                                         │
 *                                         │
 *                                    ┌────┴───┐
 *                                    │  INTR  │
 *                                    │        │
 *                         PRINTER───►│ I7     │
 *                          FLOPPY───►│ I6     │
 *                             PIR───►│ I5     │
 *                            COM1───►│ I4     │
 *                            COM2───►│ I3     │
 *                  ┌────────────────►│ I2     │
 *                  │     KEYBOARD───►│ I1     │
 *                  │          PIT───►│ I0     │
 *             ┌────┴───┐             └────────┘
 *             │  INTR  │               MASTER
 *             │        │                PIC
 *    IDE#2───►│ I7     │
 *    IDE#1───►│ I6     │
 *      FPU───►│ I5     │
 *    MOUSE───►│ I4     │
 *      PIR───►│ I3     │
 *      PIR───►│ I2     │
 *      PIR───►│ I1     │
 *  RT CLOCK──►│ I0     │
 *             └────────┘
 *               SLAVE
 *                PIC
*/

void irq_handler(regs *regdata) {
  switch (regdata->interrupt_id) {
  case PIC_INTERRUPT_PIT:
    /* update system clock. */
    pit_tick();
    break;
  case PIC_INTERRUPT_KEYBOARD:
    /* dispatch to the keyboard driver */
    keyrupt();
    break;
  default:
    break;
  }
  if (regdata->interrupt_id >= 8) {
    port_byte_write(PIC_SLV_CMND_REG, PIC_COMMAND_EOI);
  }
  port_byte_write(PIC_MTR_CMND_REG, PIC_COMMAND_EOI);
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

  port_byte_write(PIC_MTR_DATA_REG, mask_master);
  port_byte_write(PIC_SLV_DATA_REG, mask_slave);
}

void init_pic() {
  install_pic();
  asm volatile("sti");
  prints(">>PIC installed...\n");
}