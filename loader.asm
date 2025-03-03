MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 1048576

%include "gdt.asm"

[extern kernel_main]

section .bss
	align 4
	kernel_stack:
	resb KERNEL_STACK_SIZE

	align 4096
	page_directory:
	resd 1024

	align 4096
	page_table_1:
	resd 1024

	align 4096
	page_table_2:
	resd 1024


section .text
	global loader
	
	align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM
	
	loader:

		;page table for first 4mb of memory
		;identity map first 4mb of memory
		xor eax,eax
		xor ecx,ecx
		xor edx,edx

		lea eax,[page_table_1 - 0xC0000000]
		mov ecx,0 ;counter
		mov ebx,0 ;address to start mapping from


		%macro fill_page_table 0
			mov edx,ebx
			or edx,3
			mov [eax + ecx * 4],edx
			add ebx,4096
			inc ecx
		%endmacro

		%rep 1024

			fill_page_table

		%endrep

		;to the page directory,add a mapping for address 3GB + 1mb
		;this is page directory entry 768
		;lets try mapping 4mb for now,that is virtual address 3gb to (3gb + 4mb)
		xor eax,eax
		xor ecx,ecx
		xor edx,edx

		lea eax,[page_table_1 - 0xC0000000]
		or eax,3
		lea esi,[page_directory - 0xC0000000]
		mov [esi],eax

		;;map second page 
		xor eax,eax
		xor ecx,ecx
		xor edx,edx

		lea eax,[page_table_2 - 0xC0000000]
		mov ecx,0 ;counter
		mov ebx,0 ;address to start mapping from


		%rep 1024

			fill_page_table

		%endrep

		lea eax,[page_table_2 - 0xC0000000]
		or eax,3
		lea esi,[(page_directory - 0xC0000000) + 768 * 4]
		mov [esi],eax

				
		mov eax,0xdeadbabe

		lea eax,[page_directory - 0xC0000000]
		mov cr3,eax

		mov ecx,cr0
		or ecx,0x80000000
		mov cr0,ecx

		mov eax,0xdeadbabe

		lea edx,[higher_half]
		jmp edx

		higher_half:
		
		;switch to protected mode
		cli

		lgdt [gdt_descriptor]

		mov eax,cr0
		or eax,0x1
		mov cr0,eax

		
		;flush cs
		jmp KERNEL_CODE_SEGMENT:PModeMain


	PModeMain:
			
		mov ax,KERNEL_DATA_SEGMENT
		mov ds,ax
		mov ss,ax
		mov es,ax
		mov fs,ax
		mov gs,ax
		
		mov esp,kernel_stack + KERNEL_STACK_SIZE
		call kernel_main

	loop:
		jmp loop


