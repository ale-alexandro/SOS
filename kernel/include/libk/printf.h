#ifndef _LIBK_PRINTF_
#define _LIBK_PRINTF_

#include <libk/stdarg.h>
#include <libk/stdint.h>

void printf(char *fmt, ...);
char *int_to_str(size_t value, unsigned char base);

#endif
