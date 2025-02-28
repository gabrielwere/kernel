#include "keyboard.h"
#include "../x86/interrupt_handler.h"
#include "screen.h"

void keyboard_handler(stack_state_t stack_state){

	print("we have keyboard input\n");
}

void init_keyboard(){

	register_isr(&keyboard_handler,IRQ1);

}

