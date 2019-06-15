#ifndef _ARCH_X86_KHEAP_H
#define _ARCH_X86_KHEAP_H

#include <libk/stdint.h>
#include <libk/list.h>

#define KHEAP_START         0xC0000000
#define KHEAP_MIN_SIZE      0x100000

typedef struct
{
    size_t              start_addr;
    size_t              end_addr;
    size_t              max_addr;
    uint8_t               supervisor;
    uint8_t               readonly;
    struct list_head    head;
} heap_t;

typedef struct
{
    size_t              prev_foot;
    size_t              head;
    struct list_head    list;
} hchunk_t;

uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys);
uint32_t kmalloc_a(uint32_t sz);
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys);
uint32_t kmalloc(uint32_t sz);

heap_t *create_heap(uint32_t placement_addr, uint32_t start, uint32_t end,
                    uint32_t max, uint8_t supervisor, uint8_t readonly);
void *alloc(size_t bytes, heap_t *heap);
void *paligned_alloc(size_t bytes, heap_t *heap);
void free(void *p, heap_t *heap);

#endif
