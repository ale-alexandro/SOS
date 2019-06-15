.PHONY: all

CFLAGS = -c -O0 -Wall -ffreestanding -fno-builtin -nostdlib -nostdinc -fno-stack-protector -I../../kernel/include -o
CC = i686-elf-gcc
BINDIR = ../../binaries/

all: asm.o gdt.o idt.o idt_s.o timer.o kheap.o keyboard.o stdlibx86.o

asm.o:
	nasm -felf asm.S -o $(BINDIR)asm.o

gdt.o:
	$(CC) gdt.c $(CFLAGS) $(BINDIR)gdt.o

idt.o:
	$(CC) idt.c $(CFLAGS) $(BINDIR)idt.o

idt_s.o:
	nasm -felf idt.S -o $(BINDIR)idt_s.o

timer.o:
	$(CC) timer.c $(CFLAGS) $(BINDIR)timer.o

kheap.o:
	$(CC) kheap.c $(CFLAGS) $(BINDIR)kheap.o

keyboard.o:
	$(CC) keyboard.c $(CFLAGS) $(BINDIR)keyboard.o

stdlibx86.o:
	nasm -felf stdlib.S -o $(BINDIR)stdlibx86.o
