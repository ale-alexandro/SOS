//keyboard.c - Default kbd driver
//This file is a part of SmallOS Kernel
//Lenetc Alexander(aka alexandro), 2017

#include <arch/x86/keyboard.h>
#include <arch/x86/idt.h>
#include <kbmap.h>
#include <tty.h>

#define KEY_BUFFER_SIZE 16
char key_buffer[KEY_BUFFER_SIZE];
uint32_t key_buffer_head = 0;
uint32_t key_buffer_tail = 0;

void keyboard_callback()
{
  uint8_t key_code;
  inb(0x60, key_code);
  if (key_buffer_tail >= KEY_BUFFER_SIZE) {
		key_buffer_tail = 0;
	}
	key_buffer_tail++;
	key_buffer[key_buffer_tail - 1] = key_code;
	uint8_t status;
	inb(0x61, status);
	status |= 1;
	outb(0x61, status);
}

void init_keyboard()
{
  register_interrupt_handler(IRQ1, &keyboard_callback);
}

uint8_t in_scancode() {
	uint8_t result;
	if (key_buffer_head != key_buffer_tail) {
		if (key_buffer_head >= KEY_BUFFER_SIZE) {
			key_buffer_head = 0;
		}
		result = key_buffer[key_buffer_head];
		key_buffer_head++;
	} else {
		result = 0;
	}
	return result;
}


//in_char(bool) - return char from kbd buffer
char in_char(bool wait) { 
	static bool shift = false;
	uint8_t chr;
	do {
		chr = in_scancode();
		switch (chr) {
			case 0x2A:
			case 0x36:
				shift = true; //shift pressed on
				break;
			case 0x2A + 0x80:
			case 0x36 + 0x80:
				shift = false; //shift pressed out
				break;
		}
		if (chr & 0x80) {
			chr = 0; //key pressed out
		}
		if (shift) {
			chr = kbmap_shifted[chr]; 
		} else {
			chr = kbmap[chr];
		}
	} while (wait && (!chr));
	return chr;
}

//in_string(char, size_t) - read string with lenght buffer_size to buffer
void in_string(char *buffer, size_t buffer_size) {
	char chr;
	size_t position = 0;
	do {
		chr = in_char(true);
		switch (chr) {
			case 0:
				break;
			case 8:
				if (position > 0) {
					position--;
          move_cursor(getCursor() - 1);
					put0();
				}
				break;
			case '\n':
				putc('\n');
				break;
			default:
				if (position < buffer_size - 1) {
					buffer[position] = chr;
					position++;
					putc(chr);
				}
		}
	} while (chr != '\n'); //When user press "Enter", we exit from cycle of reading
	buffer[position] = 0;
}
