#include "../drivers/screen.h"
#include "../x86/interrupt_handler.h"

void main(){


//	print("booting the OS");

	set_idt();

	__asm__("int $0x3");
	__asm__("int $0x10");
	__asm__("int $0x7");

}
