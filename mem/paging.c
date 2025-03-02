#include "paging.h"

page_directory_entry_t page_directory[1024] __attribute__((aligned(4096)));
page_table_entry_t page_table_1[1024] __attribute__((aligned(4096)));

void memset(void *ptr,char character,unsigned int length){

	unsigned char *p = ptr;
	int i;
	for(i = 0;i < length;i++)
		*p++ = character;
}

void init_paging(){

	int i;

	//identity paging
	//map the lower 4mb of memory 
	memset(page_table_1,'\0',sizeof(page_table_entry_t) * 1024);

	for(i = 0;i < 1024;i++){
		page_table_1[i].memory_address = (i * 4096) >> 12;
		page_table_1[i].readwrite = 1;
		page_table_1[i].present = 1;
	}

	memset(page_directory,'\0',sizeof(page_directory_entry_t) * 1024);

	page_directory[0].page_table_address = (unsigned int)(&page_table_1) >> 12;
	page_directory[0].readwrite = 1;
	page_directory[0].present = 1;
	
	__asm__ __volatile__("mov %0,%%cr3" : : "r" (&page_directory));
	unsigned int cr0;
	__asm__ __volatile__("mov %%cr0,%0" : "=r" (cr0));

	//0x80000001;
	cr0 |= (1 << 31) | 1;
	__asm__ __volatile__("mov %0,%%cr0" : : "r" (cr0));


}
