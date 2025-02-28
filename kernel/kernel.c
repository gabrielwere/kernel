#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../x86/interrupt_handler.h"

void main(){


//	print("booting the OS");

	set_idt();

	//enable interrupts
	__asm__("sti");

	init_keyboard();

}
