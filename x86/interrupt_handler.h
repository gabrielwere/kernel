#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

extern void interrupt_handler_0();
extern void interrupt_handler_1();
extern void interrupt_handler_2();
extern void interrupt_handler_3();
extern void interrupt_handler_4();
extern void interrupt_handler_5();
extern void interrupt_handler_6();
extern void interrupt_handler_7();
extern void interrupt_handler_8();
extern void interrupt_handler_9();
extern void interrupt_handler_10();
extern void interrupt_handler_11();
extern void interrupt_handler_12();
extern void interrupt_handler_13();
extern void interrupt_handler_14();
extern void interrupt_handler_15();
extern void interrupt_handler_16();
extern void interrupt_handler_17();
extern void interrupt_handler_18();
extern void interrupt_handler_19();
extern void interrupt_handler_20();
extern void interrupt_handler_21();
extern void interrupt_handler_22();
extern void interrupt_handler_23();
extern void interrupt_handler_24();
extern void interrupt_handler_25();
extern void interrupt_handler_26();
extern void interrupt_handler_27();
extern void interrupt_handler_28();
extern void interrupt_handler_29();
extern void interrupt_handler_30();
extern void interrupt_handler_31();

typedef struct{

	unsigned int eax,ebx,ecx,edx;
	unsigned int esp,ebp,esi,edi;
	unsigned int interrupt_number,error_code;
	unsigned int eip,cs,eflags,useresp,ss;

}__attribute__((packed)) cpu_state_t;


void interrupt_handler(cpu_state_t cpu_state);
void set_idt();

#endif
