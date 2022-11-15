#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <gdt.h>
#include "idt.h"

#include "io.h"
#include "tty.h"
#include <stdio.h>


static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}


volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

// static volatile struct limine_kernel_address_request kaddr = {
//     .id = LIMINE_KERNEL_ADDRESS_REQUEST,
//     .revision = 0,
// };
// The following will be our kernel's entry point.
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
    
    printf("Testing exception 0x3\n");
    __asm__ volatile ("int $0x3");
    
    printf("Kernel load done!\n");
    printf("(-.-)");
    
    done();
}
