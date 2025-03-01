#include "keyboard.h"
#include "../x86/interrupt_handler.h"
#include "screen.h"
#include "ports.h"
#include "scancodes.h"

unsigned char read_scancode(){

	return port_byte_in(KEYBOARD_DATA_PORT);

}

void keyboard_handler(stack_state_t stack_state){

	unsigned char scancode = read_scancode();

	switch(scancode){
	
		case RIGHT_SHIFT_KEY_PRESS:
		case LEFT_SHIFT_KEY_PRESS:
			shift_status = ON;
			break;

		case RIGHT_SHIFT_KEY_RELEASE:
		case LEFT_SHIFT_KEY_RELEASE:
			shift_status = OFF;
			break;
	
		default:
			//we will only deal with ascii codes
			//this check also gets rid of key release events
			if(scancode >= 58)
				;//do nothing
			else if(shift_status)
				print(shift_scancode_lut[scancode]);
			else
				print(no_shift_scancode_lut[scancode]);
			break;
		}				

}

void init_keyboard(){

	register_isr(&keyboard_handler,IRQ1);

}


