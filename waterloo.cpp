#include "terminal.h"
#include "memtest.h"
#include "idt.h"

extern "C" void kernel_main() {
    terminal_initialize();
    terminal_writestring("STARTING CODENAME WATERLOO\n");
    terminal_writestring("LICENSED BY MIT\n");
    terminal_writestring("DELTAOSP, NBLANETWORKS, 128PROJECTS 2024\n");
    terminal_writestring("STARTING XANMEM\n");

    if (xanmem_test()) {
        terminal_writestring("Memory Test Passed!\n");
    } else {
        terminal_writestring("Memory Test Failed!\n");
    }

    terminal_writestring("Welcome to Waterloo/128OSW\n");
    terminal_writestring("128W>\n");

    idt_initialize();
    pic_remap();
    enable_interrupts();

    while (1) {}
}
