# SOS
Small OS Project 

This is my old(2017) project where i want to code my own module kernel(Not even close yet) and, maybe, Operation System

To compile this shit, you need a x86_32 cross compiler (HOW TO: https://wiki.osdev.org/GCC_Cross-Compiler)

Realized:
1. System boot-up with GRUB(Multiboot)
2. Base TTY => Inkerner 
3. Memory paging 
4. Interrupts => Keyboard, timer, etc.
5. RTC clock
6. Heap (Some dyn. memory)
7. PCI Scanning

Planned:
1. Work with PCI and SATA(through PCI bus)
2. Threading and Thread Safety(Mutexes, locks, semaphores)
3. Multitasking based on Bidirectional listings and timer interrupt
4. Some File Systems support
5. VGA Support on kernel level
6. Modules loader
