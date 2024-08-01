#include "../headers/driver/video.h"
#include "../headers/sys/common.h"
#include "../headers/util/assert.h"
#include "../headers/sys/idt.h"

void main() {
  /* As the setup is done in the wrapper function, this remains clean */
  printd(0/0);
}

void kernel_setup() {
  init_video();
  init_idt();
  main();
}