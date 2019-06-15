#include <tty.h>
#include <libk/stdlib.h>

typedef struct {
	uint8_t chr;
	uint8_t attr;
} TTYChar_t;

uint32_t	tty_width;
uint32_t 	tty_height;
uint32_t	tty_cursor;
uint8_t  	tty_attr;
TTYChar_t 	*tty_buffer;
uint16_t 	tty_io_port;

void set_tty_attr(enum vga_color bg, enum vga_color fg) {
	tty_attr = fg | bg << 4;
	int i = 0;
	while (i <= tty_width * tty_height)
	{
			tty_buffer[i].attr = tty_attr;
			i++;
	}
}

void init_tty()
{
	tty_buffer = (void*)0xB8000;
	tty_width = *((uint16_t*)0x44A);
	tty_height = 25;
        tty_io_port = *((uint16_t*)0x463);
	tty_cursor = (*((uint8_t*)0x451)) * tty_width + (*((uint8_t*)0x450));
	set_tty_attr(VGA_COLOR_BLACK, VGA_COLOR_GREEN);
}

void clear_tty() {
	memsetw(tty_buffer, (tty_attr << 8) + ' ', tty_width * tty_height);
	move_cursor(0);
}

void move_cursor(uint32_t pos) {
	tty_cursor = pos;
	if (tty_cursor >= tty_width * tty_height) {
		tty_cursor = (tty_height - 1) * tty_width;
		memcpy(tty_buffer, tty_buffer + tty_width, tty_width * tty_height * sizeof(TTYChar_t));
		memsetw(tty_buffer + tty_width * (tty_height - 1), (tty_attr << 8) + ' ', tty_width);
	}
	outb(tty_io_port, 0x0E);
	outb(tty_io_port + 1, tty_cursor >> 8);
	outb(tty_io_port, 0x0F);
	outb(tty_io_port + 1, tty_cursor & 0xFF);
}

void putc(char chr) {
	switch (chr) {
		case '\n':
			move_cursor((tty_cursor / tty_width + 1) * tty_width);
			break;
		default:
			tty_buffer[tty_cursor].chr = chr;
			tty_buffer[tty_cursor].attr = tty_attr;
			move_cursor(tty_cursor + 1);
	}
}

void put0()
{
	tty_buffer[tty_cursor].chr = 0;
	tty_buffer[tty_cursor].attr = VGA_COLOR_CYAN;
}

void puts(char *str) {
	while (*str) {
		putc(*str);
		str++;
	}
}

uint32_t getCursor()
{
	return tty_cursor;
}
