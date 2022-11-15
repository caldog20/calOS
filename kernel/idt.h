#ifndef __IDT_H
#define __IDT_H

#include <stdint.h>
#include <stddef.h>

#define IDT_SIZE 256
#define INT_ATTR 0x8E           // 0b10001110
#define KERNEL_CS 0x28
#define PIC_1_CTRL 0x20
#define PIC_2_CTRL 0xA0
#define PIC_1_DATA 0x21
#define PIC_2_DATA 0xA1


typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
} __attribute__((packed)) idt_entry_t;

// Define the interrupt handler register
typedef struct {
    uint16_t limit;
    uint64_t base;
}  __attribute__((packed)) idt_register;



extern idt_entry_t idt[IDT_SIZE];
extern idt_register idt_reg;


void idt_init(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void init_pic(void);
void except_handler(void);



#endif