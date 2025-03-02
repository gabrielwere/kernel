#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../x86/interrupt_handler.h"
#include "../mem/paging.h"

void kernel_main(){


	print("booting the OS");

	set_idt();

	init_paging();

	//enable interrupts
	__asm__("sti");


	init_keyboard();
	__asm__("int $0x5");
	print("paging enabled\n");
}
