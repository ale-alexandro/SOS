#ifndef _ARCH_X86_TIMER_H_
#define _ARCH_X86_TIMER_H_

#include <libk/stdint.h>
#include <libk/stdlib.h>

void init_timer(unsigned int frequency);
void beep();

#endif
