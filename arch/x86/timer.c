#include <arch/x86/timer.h>
#include <arch/x86/idt.h>
#include <libk/printf.h>

//uint32_t tick = 0;

void timer_callback(registers_t regs)
{
    (*((char*)(0xB8000 + 79 * 2)))++;
}

void init_timer(unsigned int freq)
{
  // Для начала регистрируем наш callback
  register_interrupt_handler(IRQ0, &timer_callback);

  // Значение, сообщаемое в PIT
  uint32_t divisor = 1193180 / freq;

  // Послать команду
  outb(0x43, 0x36);

  // Значение посылается в два этапа
  uint8_t l = (uint8_t)(divisor & 0xFF);
  uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

  // Посылаем на порт данных
  outb(0x40, l);
  outb(0x40, h);
}
