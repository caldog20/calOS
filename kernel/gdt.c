#include "gdt.h"

__attribute__((aligned(0x1000))) gdt_t gdt_table = {
    GDT_ENTRY(0, 0, 0, 0),  // null entry
    GDT_ENTRY(0, 0xffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEGMENT | GDT_ACCESS_CODE_READABLE,
              (GDT_FLAG_16BIT | GDT_FLAG_GRANULARITY_4k)),  // 16 bit code segment
    GDT_ENTRY(0, 0xffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEGMENT | GDT_ACCESS_DATA_WRITEABLE,
              (GDT_FLAG_16BIT | GDT_FLAG_GRANULARITY_4k)),  // 16 bit data segment

    GDT_ENTRY(0, 0xfffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEGMENT | GDT_ACCESS_CODE_READABLE,
              GDT_FLAG_32BIT | GDT_FLAG_GRANULARITY_4k),  // 32 bit code segment
    GDT_ENTRY(0, 0xfffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEGMENT | GDT_ACCESS_DATA_WRITEABLE,
              GDT_FLAG_32BIT | GDT_FLAG_GRANULARITY_4k),  // 32 bit data segment

    GDT_ENTRY(0, 0xfffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEGMENT | GDT_ACCESS_CODE_READABLE,
              GDT_FLAG_64BIT | GDT_FLAG_GRANULARITY_4k),  // 64 bit code segment
    GDT_ENTRY(0, 0xfffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEGMENT | GDT_ACCESS_DATA_WRITEABLE,
              GDT_FLAG_64BIT | GDT_FLAG_GRANULARITY_4k),  // 64 bit data segment
    // {0x0, 0x0, 0x0, 0x9a, 0xa0, 0x0}, // user code segment
    // {0x0, 0x0, 0x0, 0x9a, 0xa0, 0x0}, // user data segment
};

gdt_descriptor_t gdt_descriptor = {sizeof(gdt_table) - 1, &gdt_table};