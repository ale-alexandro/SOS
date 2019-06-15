#ifndef PAGING_H
#define PAGING_H

#include <libk/stdint.h>
#include <arch/x86/idt.h>

#define PAGE_SIZE           (0x1000)

typedef struct page
{
	uint32_t present	: 1;	// Страница представлена в памяти
	uint32_t rw		: 1;	// Если установлен - то read-only
	uint32_t user		: 1;	// Если сброшен - то уровень ядра
	uint32_t accessed	: 1;	// Был ли доступ к странице
	uint32_t dirty	: 1;	// Была ли запись в страницу
	uint32_t unused	: 7;	// Зарезервированные и неиспользуемые биты
	uint32_t frame	: 20;	// Адрес кадра
} page_t;

typedef struct page_table
{
	page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
	page_table_t *tables[1024];
	uint32_t tablesPhysical[1024];
} page_directory_t;

extern void init_paging();
extern void switch_page_directory(page_directory_t *new);
extern page_t *get_page(uint32_t address, int make, page_directory_t *dir);
extern void page_fault(registers_t regs);

#endif
