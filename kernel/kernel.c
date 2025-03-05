#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../x86/interrupt_handler.h"
#include "../mem/paging.h"

void kernel_main(){



	set_idt();

	init_paging();

	print("booting the OS\n");
	//enable interrupts
	__asm__("sti");


	init_keyboard();
	print("paging enabled\n");


	//generate page fault
	//unsigned int *addr = (unsigned int *)0x800000;
	unsigned int *addr = (unsigned int *)0xC0000030;
	unsigned int number = *addr;
}
