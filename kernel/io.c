#include <io.h>

uint8_t inb(uint16_t port) {
    // We're using inline assembly to read from the port

    // "=a" (result) means to put value of rax in result
    // "d" (port) means put value of port in dx

    // asm instructions use the form "command" : "output" : "input"
    // Use the "in" assembly command to read from a port
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outb(uint16_t port, uint8_t data) { __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port)); }

void outc(uint16_t port, char data) { __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port)); }

void io_wait() { outb(0x80, 0); }