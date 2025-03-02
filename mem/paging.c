#include "paging.h"
#include "../x86/interrupt_handler.h"
#include "../drivers/screen.h"

page_directory_entry_t page_directory __attribute__((aligned(4096)));
page_table_entry_t page_table_1[1024] __attribute__((aligned(4096)));

void page_fault_handler(stack_state_t stack_state){

	//the error code
	if(!(stack_state.error_code & 0x1))
		print("page is not present\n");

	if(stack_state.error_code & (1 << 1))
		print("a write operation caused the page fault\n");
	else
		print("a read operation caused the page fault\n");

	if(stack_state.error_code & (1 << 2))
		print("process was running in user mode\n");
	else
		print("process was runnnig in kernel mode\n");

	if(stack_state.error_code & (1 << 3))
		print("reserved bits were being overwritten\n");

	//for now,just stop execution by going into an infinite loop
	while(1)
		;
}

void memset(void *ptr,char character,unsigned int length){

	unsigned char *p = ptr;
	int i;
	for(i = 0;i < length;i++)
		*p++ = character;
}

void init_paging(){

	register_isr(&page_fault_handler,14);

	int i;

	//identity paging
	//map the lower 4mb of memory 
	memset(page_table_1,'\0',sizeof(page_table_entry_t) * 1024);

	for(i = 0;i < 1024;i++){
		page_table_1[i].memory_address = (i * 4096) >> 12;
		page_table_1[i].readwrite = 1;
		page_table_1[i].present = 1;
	}

	memset(&page_directory,'\0',sizeof(page_directory_entry_t));

	page_directory.page_table_address = (unsigned int)(&page_table_1) >> 12;
	page_directory.readwrite = 1;
	page_directory.present = 1;
	
	__asm__ __volatile__("mov %0,%%cr3" : : "r" (&page_directory));
	unsigned int cr0;
	__asm__ __volatile__("mov %%cr0,%0" : "=r" (cr0));

	//0x80000001;
	cr0 |= (1 << 31);
	__asm__ __volatile__("mov %0,%%cr0" : : "r" (cr0));


}


