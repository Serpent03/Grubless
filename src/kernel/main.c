#include "../headers/driver/video.h"
#include "../headers/sys/common.h"

void main() {
  init_video();
  prints("Hi world!\nHow are you?\n");
  printd(102);
}