C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
C_OBJ = $(C_SOURCES:.c=.o)

all:kernel.elf
	mv kernel.elf iso/boot/
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf-8 -quiet -boot-info-table -o os.iso iso

kernel.elf:loader.o $(C_OBJ)
	i386-elf-ld -T linker.ld $^ -o $@

%.o : %.asm
	nasm -f elf $<

%.o : %.c
	i386-elf-gcc -ffreestanding -c $< -o $@

clean:
	rm *.o iso/boot/kernel.elf bochslog.txt kernel/*.o drivers/*.o
	
bochs:
	bochs -f bochsrc.txt -q

log:
	cat bochslog.txt


