#include "idt.h"

#include <string.h>

#include "io.h"
#include "kbmap.h"
#include "pic.h"
#include "stdio.h"
#include "tty.h"

// Provide definitions for our extern values
__attribute__((aligned(0x10))) idt_entry_t idt[IDT_SIZE];
idt_register idt_reg;
isr_t interrupt_handlers[256];
extern void* isr_stub_table[];
extern void* irq_stub_table[];
extern void kb_handler(void);
void idt_set_descriptor(uint8_t vector, uintptr_t isr, uint8_t flags, uint8_t ist) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->base_low = isr & 0xFFFF;
    descriptor->cs = 0x28;
    descriptor->ist = ist;
    descriptor->attributes = flags;
    descriptor->base_mid = (isr >> 16) & 0xFFFF;
    descriptor->base_high = (isr >> 32) & 0xFFFFFFFF;
    descriptor->rsv0 = 0;
}

void idt_init() {
    idt_reg.base = (uintptr_t)&idt[0];
    idt_reg.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    // ISR Handler stubs
    for (uint8_t vector = 0; vector < IDT_CPU_EXCEPTION_COUNT; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], IDT_DESCRIPTOR_EXCEPTION, 0);
    }

    // IRQ Handler stubs
    for (uint8_t vector = 0; vector < 16; vector++) {
        idt_set_descriptor(vector + IDT_CPU_EXCEPTION_COUNT, irq_stub_table[vector], IDT_DESCRIPTOR_EXCEPTION, 0);
    }

    // Register specific hardware interrupt handlers here
    register_interrupt_handler(IRQ1, &kb_isr);

    __asm__ volatile("lidt %0" : : "m"(idt_reg));  // load the new IDT
    __asm__ volatile("sti");                       // set the interrupt flag
}

void kb_init() {
    uint8_t curmask = inb(0x21);
    outb(0x21, curmask & 0xFD);
}

void kb_isr(isr_xframe_t* frame) {
    int8_t keycode = inb(0x60);
    if (keycode >= 0 && keyboard_map[keycode]) {
        printf("%c", keyboard_map[keycode]);
    }

    pic_send_eoi(1);
}

void isr_handler(isr_xframe_t* frame) {
    printf("Int %d Err %d\n", frame->base_frame.vector, frame->base_frame.error_code);
    __asm__ volatile("cli; hlt");
}

void irq_handler(isr_xframe_t* frame) {
    // pic_eoi(regs.intNo);
    // printf("IRQ %d\n", frame->base_frame.vector);
    isr_t handler = interrupt_handlers[frame->base_frame.vector];
    handler(frame);
}

void register_interrupt_handler(uint8_t n, isr_t handler) { interrupt_handlers[n] = handler; }
