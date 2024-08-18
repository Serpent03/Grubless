#include "../../headers/sys/isr.h"
#include "../../headers/driver/video.h"

void handle_interrupts(regs *regdata) {
  // printf("Interrupt: %d, error code: %d\n", 2, regdata->interrupt_id,
  //  regdata->error_code);
  switch (regdata->interrupt_id) {
  case INTR_DIV_BY_ZERO:
    for (;;) {
    }
  case INTR_DOUBLE_FAULT:
    for (;;) {
    }
  default:
    break;
  }
}
