#ifndef _ARCH_X86_KEYBOARD_H
#define _ARCH_X86_KEYBOARD_H

#include <libk/stdlib.h>

void init_keyboard();
uint8_t in_scancode();
char in_char(bool);
void in_string(char *buffer, size_t buffer_size);

#endif
