#include <libk/stdlib.h>

size_t strlen(char *str) {
	return (char*)memchr(str, '\0', -1) - str;
}

void strcpy(char *dest, char *src) {
	memcpy(dest, src, strlen(src) + 1);
}

void strncpy(char *dest, char *src, size_t max_count) {
	size_t len = min(max_count - 1, strlen(src));
	memcpy(dest, src, len);
	dest[len] = '\0';
}

int strcmp(char *str1, char *str2) {
	return memcmp(str1, str2, strlen(str1) + 1);
}

char *strchr(char *str, char value) {
	return memchr(str, value, strlen(str));
}

bool mutex_get(Mutex
*mutex, bool wait) {
	bool old_value = true;
	do {
		asm("xchg (,%1,), %0":"=a"(old_value):"b"(mutex),"a"(old_value));
	} while (old_value && wait);
	return !old_value;
}

void mutex_release(Mutex *mutex) {
	*mutex = false;
}
