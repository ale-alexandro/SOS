#ifndef PANIC_H
#define PANIC_H

#define ASSERT(a) if(!(a)) panic(a)

void panic(char *chr);

#endif
