#include "idt.h"
#include "port_io.h"

struct IDTEntry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));

struct IDTPointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define NUM_IDT_ENTRIES 256
IDTEntry idt[NUM_IDT_ENTRIES];
IDTPointer idt_ptr;

extern "C" void load_idt(void* idt_ptr);

void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_initialize() {
    idt_ptr.limit = (sizeof(IDTEntry) * NUM_IDT_ENTRIES) - 1;
    idt_ptr.base = (uint32_t) &idt;

    for (int i = 0; i < NUM_IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    idt_set_gate(33, (uint32_t) keyboard_handler, 0x08, 0x8E);

    load_idt(&idt_ptr);
}

void pic_remap() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

extern "C" void enable_interrupts();
