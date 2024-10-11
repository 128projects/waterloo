#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize();
void terminal_putchar(char c);
void terminal_writestring(const char* data);

#endif
