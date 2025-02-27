gdt_start:
dd 0x0
dd 0x0

kernel_code_seg:
dw 0xffff
dw 0x0
db 0x0
db 10011011b
db 11001111b
db 0x0

kernel_data_seg:
dw 0xffff
dw 0x0
db 0x0
db 10010011b
db 11001111b
db 0x0


gdt_end:


gdt_descriptor:
dw gdt_end - gdt_start - 1
dd gdt_start

KERNEL_CODE_SEGMENT equ kernel_code_seg - gdt_start
KERNEL_DATA_SEGMENT equ kernel_data_seg - gdt_start
