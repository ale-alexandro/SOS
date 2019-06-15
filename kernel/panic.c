#include <panic.h>
#include <libk/printf.h>

void panic(char *chr)
{
  printf("PANIC! %s", chr);
  asm volatile("cli\n  hlt");
  while(1);
}
