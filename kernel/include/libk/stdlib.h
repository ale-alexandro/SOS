#ifndef LIBK_STDLIB_H
#define LIBK_STDLIB_H

#define NULL ((void*)0)

typedef enum {
	false = 0,
	true = 1
} bool;

typedef bool Mutex;

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#define outb(port, value) asm volatile("outb %b0, %w1"::"a"(value),"d"(port));
#define outw(port, value) asm volatile("outw %w0, %w1"::"a"(value),"d"(port));
#define outl(port, value) asm volatile("outl %0, %w1"::"a"(value),"d"(port));

#define inb(port, out_value) asm volatile("inb %w1, %b0":"=a"(out_value):"d"(port));
#define inw(port, out_value) asm volatile("inw %w1, %w0":"=a"(out_value):"d"(port));
#define inl(port, out_value) asm volatile("inl %w1, %0":"=a"(out_value):"d"(port));

#include <libk/stdint.h>

//Для указателей))
static inline void inb_p (uint16_t port, uint8_t *data)
{ asm volatile ("inb %%dx, %%al" : "=a" (*data) : "d" (port)); }
static inline void inw_p (uint16_t port, uint16_t *data)
{ asm volatile ("inw %%dx, %%ax" : "=a" (*data) : "d" (port)); }
static inline void inl_p (uint16_t port, uint32_t *data)
{ asm volatile ("inl %%dx, %%eax" : "=a" (*data) : "d" (port)); }
static inline void outb_p (uint16_t port, uint8_t data)
{ asm volatile ("outb %%al, %%dx" : : "a" (data), "d" (port)); }
static inline void outw_p (uint16_t port, uint16_t data)
{ asm volatile ("outw %%ax, %%dx" : : "a" (data), "d" (port)); }
static inline void outl_p (uint16_t port, uint32_t data)
{ asm volatile ("outl %%eax, %%dx" : : "a" (data), "d" (port)); }

void 	memset(void *mem, char value, size_t count);
void 	memsetw(void *mem, uint16_t value, size_t count);
void 	memcpy(void *dest, void *src, size_t count);
int 	memcmp(void *mem1, void *mem2, size_t count);
void 	*memchr(void *mem, char value, size_t count);

size_t 	strlen(char *str);
void 	strcpy(char *dest, char *src);
void 	strncpy(char *dest, char*src, size_t max_count);
int 	strcmp(char *str1, char *str2);
char 	*strchr(char *str, char value);

bool mutex_get(Mutex *mutex, bool wait);
void mutex_release(Mutex *mutex);

#endif
