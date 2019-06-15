#include <libk/printf.h>
#include <tty.h>

const char digits[] = "0123456789ABCDEF";
char num_buffer[65];

char *int_to_str(size_t value, unsigned char base) {
	size_t i = sizeof(num_buffer) - 1;
	num_buffer[i--] = '\0';
	do {
		num_buffer[i--] = digits[value % base];
		value = value / base;
	} while (value);
	return &num_buffer[i + 1];
}

void printf(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	while (*fmt) {
		if (*fmt == '%') {
			fmt++;
			size_t arg = va_arg(args, size_t);
			switch (*fmt) {
				case '%':
					putc('%');
					break;
				case 'c':
					putc(arg);
					break;
				case 's':
					puts((char*)arg);
					break;
				case 'b':
					puts(int_to_str(arg, 2));
					break;
				case 'o':
					puts(int_to_str(arg, 8));
					break;
				case 'd':
					puts(int_to_str(arg, 10));
					break;
				case 'x':
					puts(int_to_str(arg, 16));
					break;
			}
		} else {
			putc(*fmt);
		}
		fmt++;
	}
	va_end(args);
}
