#ifndef IDT_H
#define IDT_H

#define KERNEL_CODE_SEGMENT 0x08
#define IDT_ENTRIES 256

typedef struct{

	unsigned short low_offset;
	unsigned short segment_selector;
	unsigned char reserved;
	unsigned char attributes;
	unsigned short high_offset;

}__attribute__((packed)) idt_entry_t;

idt_entry_t idt[IDT_ENTRIES];

typedef struct{

	unsigned short size;
	unsigned int offset;

}__attribute__((packed)) idt_descriptor_t;

void set_idt_entry(unsigned int address,int entry_number);

void load_idt();


#endif
