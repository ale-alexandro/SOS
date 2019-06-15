MACHINE_X86 = qemu-system-x86_64
CC = i686-elf-gcc
CCFLAGS = -ffreestanding -nostdlib ./binaries/*.o -lgcc -o kernel_x86_v0.0.bin
LS_X86 = arch/x86/linker.ld

all_x86:
	make -C arch/x86/
	make -C kernel/
	$(LD) -T $(LS_X86) $(CCFLAGS)
	mkdir -p iso/boot/grub
	cp kernel_x86_v0.0.bin iso/boot/kernel_x86_v0.0.bin
	cp ./grub.cfg ./iso/boot/grub/grub.cfg
	grub-mkrescue -o SOS.iso iso/
	rm -rf iso/
	rm ./binaries/*.o

test_x86:
	$(MACHINE_X86) -cdrom SOS.iso
