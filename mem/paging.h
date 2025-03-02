#ifndef PAGING_H
#define PAGING_H

typedef struct{

	unsigned char present : 1;
	unsigned char readwrite : 1;
	unsigned char user : 1;
	unsigned char writethrough : 1;
	unsigned char cachedisable : 1;
	unsigned char accessed : 1;
	unsigned char zero : 1;
	unsigned char pagesize : 1;
	unsigned char available : 4;
	unsigned int page_table_address : 20;

}__attribute__((packed)) page_directory_entry_t;


typedef struct{

	unsigned char present : 1;
	unsigned char readwrite : 1;
	unsigned char user : 1;
	unsigned char writethrough : 1;
	unsigned char cachedisable : 1;
	unsigned char accessed : 1;
	unsigned char dirty : 1;
	unsigned char pageattributetable : 1;
	unsigned char global : 1;
	unsigned char available : 3;
	unsigned int memory_address : 20;

}__attribute__((packed)) page_table_entry_t;

void init_paging();

#endif
