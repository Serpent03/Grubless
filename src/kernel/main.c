#include "../headers/driver/video.h"
#include "../headers/sys/common.h"
#include "../headers/util/assert.h"
#include "../headers/sys/idt.h"
#include "../headers/driver/pic.h"

void main() {
  /* As the setup is done in the wrapper function, this remains clean */
  prints("done\n");
}

void kernel_setup() {
  init_video();
  init_idt();
  init_pic();
  main();
}