;multiboot header, startup code and support asm code

MULTIBOOT_PG_ALIGN 	EQU 1<<0
MULTIBOOT_MEM_INFO	EQU 1<<1
MULTIBOOT_MAGIC 		EQU 0x1BADB002
MULTIBOOT_FLAGS 		EQU MULTIBOOT_PG_ALIGN | MULTIBOOT_MEM_INFO
MULTIBOOT_CHECKSUM  EQU - (MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
KERNEL_STACK_SIZE		EQU 0x4000

[BITS 32]
[GLOBAL multiboot]
[GLOBAL _startup]
[GLOBAL GDTflush]
[GLOBAL IDTflush]
[GLOBAL jumpToRing3]
[EXTERN kmain]

section .text

mboot:
ALIGN 4
dd 	MULTIBOOT_MAGIC
dd 	MULTIBOOT_FLAGS
dd 	MULTIBOOT_CHECKSUM

_startup:
	mov 	esp, KERNEL_STACK + KERNEL_STACK_SIZE
	push 	ebx
	push 	eax
	cli
	call	kmain
	jmp 	$
	cli
	hlt

GDTflush:
	mov 	eax, [esp+4]	       	; Get pointer to GDT
	lgdt 	[eax]                	; Load this pointer to GDT
	mov 	ax, 0x10            	; 0x10 - merge of DATA segment
	mov 	ds, ax
	mov 	es, ax
	mov 	fs, ax
	mov 	gs, ax
	mov 	ss, ax
	jmp 	0x08:.flush            			; 0x08 - merge of LONG segment : do long jump
.flush:
	ret

IDTflush:
	mov 	eax, [esp+4]
	lidt 	[eax]
	sti
	ret

section .bss

ALIGN 32
KERNEL_STACK:
	RESB	KERNEL_STACK_SIZE
