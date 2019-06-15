#ifndef _ARCH_X86_GDT_H
#define _ARCH_X86_GDT_H

#include <libk/stdint.h>

typedef struct {
    uint16_t      limit_low;      // Младшие 16 бит смещения
    uint16_t      base_low;       // Младшие 16 бит базы
    uint8_t       base_middle;    // Следующие восемь бит базы
    uint8_t       access;         // Флаг определяет уровень доступа
    uint8_t       granularity;
    uint8_t       base_high;      // старшие 8 бит базы

} __attribute__((packed)) gdt_entry_t;

typedef struct {
  uint16_t        limit;    // старшие 16 бит смещения селектора
  uint32_t        base;     // адрес первой структуры gdt_entry_t

} __attribute__((packed)) gdt_ptr_t;

void initGDT();
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif
