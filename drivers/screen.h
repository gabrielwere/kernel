#ifndef SCREEN_H
#define SCREEN_H

#define COMMAND_PORT 0x3d4
#define DATA_PORT 0x3d5
#define HIGH_BYTE 14
#define LOW_BYTE 15
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define VGA_ADDRESS 0xC00B8000

void print(unsigned char *word);

#endif
