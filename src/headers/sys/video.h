#pragma once

#include "./common.h"

#define VMEMLOC 0xb8000
#define WIDTH 80
#define HEIGHT 25
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

enum COLOR {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
};

/* Write character C to the video terminal. */
void printch(uint8 c);

/* Write string STR to the video terminal. */
void prints(uint8 *str);

/* Clear out the video terminal. */
void cls();

/* Set foreground video terminal color to COL. */
void set_fg_color(uint8 col);

/* Set background video terminal color to COL. */
void set_bg_color(uint8 col);

/* Set the hardware cursor to a pixel N. */
void set_cursor(uint16 n);

/* Get linear memory mapping from coordinates (X, Y). 0-indexed */
uint16 xyton(uint16 x, uint16 y);

/* Initialize the video drivers. */
void init_video();

