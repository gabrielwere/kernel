#include "idt.h"

void set_idt_entry(unsigned int address,int entry_number){

	idt[entry_number].low_offset = (unsigned short)(address & 0xffff);
	idt[entry_number].segment_selector = KERNEL_CODE_SEGMENT;
	idt[entry_number].reserved = 0;
	idt[entry_number].attributes = 0x8E;
	idt[entry_number].high_offset = (unsigned short)((address >> 16) & 0xffff);

}

void load_idt(){

	idt_descriptor_t idt_descriptor;

	idt_descriptor.size = IDT_ENTRIES * (sizeof(idt_entry_t)) - 1;
	idt_descriptor.offset = (unsigned int)&idt;

	__asm__("lidt (%0)" : : "r" (&idt_descriptor));

}
