#include <stdint.h>
#include "port_io.h"
#include "terminal.h"

#define KEYBOARD_PORT 0x60

unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0
};

extern "C" void keyboard_handler() {
    uint8_t scancode = inb(KEYBOARD_PORT);

    if (scancode & 0x80) {
        return;
    }

    char key = keyboard_map[scancode];
    if (key) {
        terminal_putchar(key);
    }
}
