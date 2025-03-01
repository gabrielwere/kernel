#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_DATA_PORT 0x60

void init_keyboard();

#define ON 1
#define OFF 0

static char shift_status = OFF;


#endif
