[extern interrupt_handler]

%macro no_error_code_interrupt_handler 1

	global interrupt_handler_%1

	interrupt_handler_%1:
		cli ;no interrupts within the interrupt
		push dword 0 ;dummy error code
		push dword %1 ;interrupt number
		jmp common_interrupt_handler

%endmacro


%macro error_code_interrupt_handler 1

	global interrupt_handler_%1

	interrupt_handler_%1:
		cli
		push dword %1 ;interrupt number;
		jmp common_interrupt_handler

%endmacro


common_interrupt_handler:
	
	pushad

	call interrupt_handler

	popad

	add esp,8
	sti
	iret


;the first 32 interrupts are reserved for the cpu
;they must therefore be set i.e they are not allowed to not exist
;of the 32,only interrupt 8,10,11,12,13,14 and 17 push error codes

no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
no_error_code_interrupt_handler 7
error_code_interrupt_handler 8
no_error_code_interrupt_handler 9
error_code_interrupt_handler 10
error_code_interrupt_handler 11
error_code_interrupt_handler 12
error_code_interrupt_handler 13
error_code_interrupt_handler 14
no_error_code_interrupt_handler 15
no_error_code_interrupt_handler 16
error_code_interrupt_handler 17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20
no_error_code_interrupt_handler 21
no_error_code_interrupt_handler 22
no_error_code_interrupt_handler 23
no_error_code_interrupt_handler 24
no_error_code_interrupt_handler 25
no_error_code_interrupt_handler 26
no_error_code_interrupt_handler 27
no_error_code_interrupt_handler 28
no_error_code_interrupt_handler 29
no_error_code_interrupt_handler 30
no_error_code_interrupt_handler 31
