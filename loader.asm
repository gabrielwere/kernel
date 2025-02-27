MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 4096

%include "gdt.asm"

[extern main]

section .bss
	align 4
	kernel_stack:
	resb KERNEL_STACK_SIZE

section .text
	global loader
	
	align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM
	
	loader:
		mov eax,0xcafebabe
		
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
		call main

	loop:
		jmp loop


