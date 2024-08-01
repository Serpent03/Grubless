#include "../headers/driver/video.h"
#include "../headers/sys/common.h"
#include "../headers/util/assert.h"
#include "../headers/sys/idt.h"

void main() {
  /* As the setup is done in the wrapper function, this remains clean */
  prints("Hello world, this is me from the kernel_main()\nSo this is it..\n");
  asm volatile("int  $3");
  prints("\nThis should load.");
}

void kernel_setup() {
  init_video();
  init_idt();
  main();
}