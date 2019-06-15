.PHONY: all

CFLAGS = -c -O0 -Wall -ffreestanding -fno-builtin -nostdlib -nostdinc -fno-stack-protector -Iinclude -o
CC = i686-elf-gcc
BINDIR = ../binaries/

all: kmain.o tty.o stdlib.o printf.o panic.o paging.o kterm.o rtc.o pci.o

kmain.o: kmain.c
	$(CC) kmain.c $(CFLAGS) $(BINDIR)kmain.o

tty.o: tty.c
	$(CC) tty.c $(CFLAGS) $(BINDIR)tty.o

stdlib.o: stdlib.c
	$(CC) stdlib.c $(CFLAGS) $(BINDIR)stdlib.o

printf.o: printf.c
	$(CC) printf.c $(CFLAGS) $(BINDIR)printf.o

panic.o: panic.c
	$(CC) panic.c $(CFLAGS) $(BINDIR)panic.o

paging.o:
	$(CC) paging.c $(CFLAGS) $(BINDIR)paging.o

kterm.o:
	$(CC) kterm.c $(CFLAGS) $(BINDIR)kterm.o

rtc.o:
	$(CC) rtc.c $(CFLAGS) $(BINDIR)rtc.o

pci.o:
	$(CC) pci.c $(CFLAGS) $(BINDIR)pci.o
