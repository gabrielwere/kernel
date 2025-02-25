#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_REG_CTRL 0x3d4
#define SCREEN_REG_DATA 0x3d5
#define HIGH_BYTE 14
#define LOW_BYTE 15
#define MAX_ROWS 25
#define MAX_COLS 80
#define VGA_ADDRESS 0xb8000
#define WHITE_ON_BLACK 0x0f

void print(unsigned char *word);

#endif
