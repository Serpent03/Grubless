#include "../headers/driver/pic.h"
#include "../headers/driver/video.h"
#include "../headers/sys/common.h"
#include "../headers/sys/idt.h"
#include "../headers/sys/systimer.h"
#include "../headers/util/assert.h"

/* main is a special C keyword - that's why I'm naming the kernel entry as
 * k_main instead */
void k_main() {
  /* As the setup is done in the wrapper function, this remains clean */
}

void kernel_setup() {
  init_video();
  init_idt();
  init_pic();
  init_sysclock();
  sleep(4000);
  cls();
  k_main();
}