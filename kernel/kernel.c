#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <gdt.h>
#include "idt.h"

#include "io.h"
#include <tty.h>
#include <stdio.h>
#include "pic.h"
#include "serial.h"

static void done(void) {
    __asm__("cli");
    for (;;) {
        __asm__("hlt");
    }
}

volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

void _start(void) {

    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
    }
    printf("Loading Kernel\n");
    printf("Loading GDT\n");
    load_gdt(&gdt_descriptor);

    printf("Loading IDT\n");
    idt_init();
    
    printf("Initializing Pic\n");
    pic_remap_offsets(0x20);
    printf("Unmasking keyboard interrupt\n");
    pic_unmask_irq(1);
    kb_init();
    
    printf("Kernel load done!\n");
    printf("(-.-)\n");
    serial_terminal()->puts("\nTesting Serial\n");

    while(1) {

    }

    
}
