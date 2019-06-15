#include <kterm.h>
#include <tty.h>
#include <libk/printf.h>
#include <libk/stdlib.h>
#include <pci.h>
#include <rtc.h>

void alias()
{
  printf("Commands avaliable:\n about, alias, lspci, time, clear, heap_test\n");
}

void time()
{
  time_t cur_time;
  cur_time = read_rtc();
  printf("Time: %d:%d:%d\n", cur_time.hour, cur_time.minute, cur_time.second);
  printf("Date: %d.%d.%d\n", cur_time.day, cur_time.month, cur_time.year);
}

void heap_test()
{
  unsigned int a = kmalloc(8);
	unsigned int b = kmalloc(8);
	printf("a: %x\n", a);
	printf("b: %x\n", b);
	kfree(a);
  kfree(b);
  unsigned int c = kmalloc(12);
  printf("c: %x\n", c);
}

void kterm()
{
  printf("Welcome to Small OS v0.1! \n\"Alias\" command shows U avaliable commands\n");
  while (1) {
		char buffer[256];
		printf("> ");
		in_string(buffer, sizeof(buffer));
		if (strcmp(buffer, "about") == 0)
		  printf("SOS v0.1 by Alexander Lenets 2017\n");
    else if(strcmp(buffer, "alias") == 0)
      alias();
    else if(strcmp(buffer, "lspci") == 0)
      PCIScan();
    else if(strcmp(buffer, "time") == 0)
      time();
    else if(strcmp(buffer, "clear") == 0)
      clear_tty();
    else if(strcmp(buffer, "heap_test") == 0)
      heap_test();
    else
      printf("Unknown command:(\n");
	}
}
