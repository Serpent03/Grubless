#include "../headers/driver/pic.h"
#include "../headers/driver/video.h"
#include "../headers/driver/keyboard.h"
#include "../headers/sys/common.h"
#include "../headers/sys/idt.h"
#include "../headers/sys/systimer.h"
#include "../headers/driver/pci.h"
#include "../headers/util/assert.h"
#include "../headers/util/string.h"

/* main is a special C keyword - that's why I'm naming the kernel entry as
 * k_main instead */
void k_main() {
  /* As the setup is done in the wrapper function, this remains clean */
  printf("Yo there from %s land. Bootup @ %dms with charset %c\n", "FAT12", get_time(), 'c');
}

void kernel_setup() {
  init_video();
  init_idt();
  init_pic();
  init_ps2();
  init_sysclock();
  init_pci();
  sleep_s(600);
  cls();
  /* k_main() is called by boot2kernel. */
}