#include "idt.h"
#include "tty.h"
// Provide definitions for our extern values
__attribute__((aligned(0x10))) 
idt_entry_t idt[IDT_SIZE];
idt_register idt_reg;


// __attribute__((noreturn))
void exception_handler() {
    // __asm__ volatile ("cli; hlt"); // Completely hangs the computer
    terminal_writestring(terminal_request, "exception handler fired!\n");
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low       = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs     = 0x28;
    descriptor->ist           = 0;
    descriptor->attributes    = flags;
    descriptor->isr_mid       = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high      = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved      = 0;
}

extern void* isr_stub_table[];
 

void idt_init() {
    idt_reg.base = (uintptr_t)&idt[0];
    idt_reg.limit = (uint16_t)sizeof(idt_entry_t) * 256 - 1;
 
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        // vectors[vector] = 1;
    }
 
    __asm__ volatile ("lidt %0" : : "m"(idt_reg)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}

void init_pic() {
	outb(PIC_1_CTRL, 0x11);
	outb(PIC_2_CTRL, 0x11);

	outb(PIC_1_DATA, 0x20);
	outb(PIC_2_DATA, 0x28);

	outb(PIC_1_DATA, 0x00);
	outb(PIC_2_DATA, 0x00);

	outb(PIC_1_DATA, 0x01);
	outb(PIC_2_DATA, 0x01);

	outb(0x21, 0xFF);
	outb(0xA1, 0xFF);
}

