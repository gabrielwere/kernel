#include "interrupt_handler.h"
#include "idt.h"
#include "../drivers/screen.h"

void set_idt(){


	set_idt_entry((unsigned int)interrupt_handler_0,0);
	set_idt_entry((unsigned int)interrupt_handler_1,1);
	set_idt_entry((unsigned int)interrupt_handler_2,2);
	set_idt_entry((unsigned int)interrupt_handler_3,3);
	set_idt_entry((unsigned int)interrupt_handler_4,4);
	set_idt_entry((unsigned int)interrupt_handler_5,5);
	set_idt_entry((unsigned int)interrupt_handler_6,6);
	set_idt_entry((unsigned int)interrupt_handler_7,7);
	set_idt_entry((unsigned int)interrupt_handler_8,8);
	set_idt_entry((unsigned int)interrupt_handler_9,9);
	set_idt_entry((unsigned int)interrupt_handler_10,10);
	set_idt_entry((unsigned int)interrupt_handler_11,11);
	set_idt_entry((unsigned int)interrupt_handler_12,12);
	set_idt_entry((unsigned int)interrupt_handler_13,13);
	set_idt_entry((unsigned int)interrupt_handler_14,14);
	set_idt_entry((unsigned int)interrupt_handler_15,15);
	set_idt_entry((unsigned int)interrupt_handler_16,16);
	set_idt_entry((unsigned int)interrupt_handler_17,17);
	set_idt_entry((unsigned int)interrupt_handler_18,18);
	set_idt_entry((unsigned int)interrupt_handler_19,19);
	set_idt_entry((unsigned int)interrupt_handler_20,20);
	set_idt_entry((unsigned int)interrupt_handler_21,21);
	set_idt_entry((unsigned int)interrupt_handler_22,22);
	set_idt_entry((unsigned int)interrupt_handler_23,23);
	set_idt_entry((unsigned int)interrupt_handler_24,24);
	set_idt_entry((unsigned int)interrupt_handler_25,25);
	set_idt_entry((unsigned int)interrupt_handler_26,26);
	set_idt_entry((unsigned int)interrupt_handler_27,27);
	set_idt_entry((unsigned int)interrupt_handler_28,28);
	set_idt_entry((unsigned int)interrupt_handler_29,29);
	set_idt_entry((unsigned int)interrupt_handler_30,30);
	set_idt_entry((unsigned int)interrupt_handler_31,31);

	load_idt();
}

char *interrupt_messages[] = {

	"Divide by 0\n",
	"Reserved\n",
	"NMI interrupt\n",
	"Breakpoint\n",
	"Overflow\n",
	"Bounds range exceeded\n",
	"Invalid opcode\n",
	"Device not available\n",
	"Double fault\n",
	"Coprocessor segment overun\n",
	"Invalid TSS\n",
	"Segment not present\n",
	"Stack-segment fault\n",
	"General protection fault\n",
	"Page fault\n",
	"Reserved\n",
	"x87 FPU error\n",
	"Alignment check\n",
	"Machine check\n",
	"SIMD Floating-Point exception\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n",
	"Reserved\n"

};

void interrupt_handler(cpu_state_t cpu_state){

	print(interrupt_messages[cpu_state.interrupt_number]);

}


