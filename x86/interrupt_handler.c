#include "interrupt_handler.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"

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


	//you have to remap the PIC
	//the PIC uses interrupts 0 - 15,which conflicts with our CPU interrupts
	//we remap the PIC to use interrupts 32 - 47
	port_byte_out(0x20, 0x11);
	port_byte_out(0xA0, 0x11);
	port_byte_out(0x21, 0x20);
	port_byte_out(0xA1, 0x28);
	port_byte_out(0x21, 0x04);
	port_byte_out(0xA1, 0x02);
	port_byte_out(0x21, 0x01);
	port_byte_out(0xA1, 0x01);
	port_byte_out(0x21, 0x0);
	port_byte_out(0xA1, 0x0);	

	set_idt_entry((unsigned int)irq_handler_0,IRQ0);
	set_idt_entry((unsigned int)irq_handler_1,IRQ1);
	set_idt_entry((unsigned int)irq_handler_2,IRQ2);
	set_idt_entry((unsigned int)irq_handler_3,IRQ3);
	set_idt_entry((unsigned int)irq_handler_4,IRQ4);
	set_idt_entry((unsigned int)irq_handler_5,IRQ5);
	set_idt_entry((unsigned int)irq_handler_6,IRQ6);
	set_idt_entry((unsigned int)irq_handler_7,IRQ7);
	set_idt_entry((unsigned int)irq_handler_8,IRQ8);
	set_idt_entry((unsigned int)irq_handler_9,IRQ9);
	set_idt_entry((unsigned int)irq_handler_10,IRQ10);
	set_idt_entry((unsigned int)irq_handler_11,IRQ11);
	set_idt_entry((unsigned int)irq_handler_12,IRQ12);
	set_idt_entry((unsigned int)irq_handler_13,IRQ13);
	set_idt_entry((unsigned int)irq_handler_14,IRQ14);
	set_idt_entry((unsigned int)irq_handler_15,IRQ15);

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

void interrupt_handler(stack_state_t stack_state){

	print(interrupt_messages[stack_state.interrupt_number]);

}


void irq_handler(stack_state_t stack_state){

	//send a message to the PIC that the interrupt has been handled
	//this message is an end of interrupt(EOI) signal that allows the PIC
	//to generate more interrupts
	if(stack_state.interrupt_number >= 40)
		port_byte_out(0xA0,0x20);

	port_byte_out(0x20,0x20);

	if(interrupt_service_routines[stack_state.interrupt_number] != 0){

		isr_t handler = interrupt_service_routines[stack_state.interrupt_number];
		handler(stack_state);
	}

}

void register_isr(isr_t handler,int number){

	interrupt_service_routines[number] = handler;
}
