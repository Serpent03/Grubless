#pragma once

#include "../sys/common.h"

#define VMEMLOC 0xb8000
#define WIDTH 80
#define HEIGHT 25
#define CRT_ADDR_REG 0x3D4
#define CRT_DATA_REG 0x3D5

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

enum ARG_TYPE {
  ARG_TYPE_CHR = 0,
  ARG_TYPE_STR = 1,
  ARG_TYPE_INT = 2,
  ARG_TYPE_HEX = 3,
  ARG_TYPE_ESC = 4,
};

/* Write character C to the video terminal. */
void printch(uint8 c);

/* Write string STR to the video terminal. */
void prints(int8 *str);

/* Write integer D to the video terminal. */
void printd(int32 d);

/* Write hex H to the video terminal. */
void printh(uint32 h);

/* Write formatted string PATTERN to video terminal. */
void printf(char *pattern, ...);

/* Clear out the video terminal. */
void cls();

/* Set foreground video terminal color to COL. */
void set_fg_color(uint8 col);

/* Set background video terminal color to COL. */
void set_bg_color(uint8 col);

/* Set the hardware cursor to a pixel N. */
void set_cursor(uint16 n);

/* Scroll the screen by N lines. */
void scroll(uint16 n);

/* Get linear memory mapping from coordinates (X, Y). 0-indexed */
uint16 xyton(uint16 x, uint16 y);

/* Initialize the video drivers. */
void init_video();
