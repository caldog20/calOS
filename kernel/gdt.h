#ifndef __GDT_H
#define __GDT_H

#include <stdint.h>

typedef enum {
    GDT_ACCESS_CODE_READABLE = 0x02,
    GDT_ACCESS_DATA_WRITEABLE = 0x02,
    GDT_ACCESS_CODE_CONFORMING = 0x04,
    GDT_ACCESS_DATA_DIRECTION_NORMAL = 0x00,
    GDT_ACCESS_DATA_DIRECTION_DOWN = 0x04,
    GDT_ACCESS_DATA_SEGMENT = 0x10,
    GDT_ACCESS_CODE_SEGMENT = 0x18,
    GDT_ACCESS_DESCRIPTOR_TSS = 0x00,

    GDT_ACCESS_RING0 = 0x00,
    GDT_ACCESS_RING1 = 0x20,
    GDT_ACCESS_RING2 = 0x40,
    GDT_ACCESS_RING3 = 0x60,

    GDT_ACCESS_PRESENT = 0x80,
} GDT_ACCESS;

typedef enum {
    GDT_FLAG_64BIT = 0x20,
    GDT_FLAG_32BIT = 0x40,
    GDT_FLAG_16BIT = 0x00,

    GDT_FLAG_GRANULARITY_1B = 0x00,
    GDT_FLAG_GRANULARITY_4k = 0x80
} GDT_FLAGS;

#define GDT_LIMIT_LOW(limit) (limit & 0xffff)
#define GDT_BASE_LOW(base) (base & 0xffff)
#define GDT_BASE_MIDDLE(base) ((base >> 16) & 0xff)
#define GDT_FLAGS_LIMIT_HI(limit, flags) (((limit >> 16) & 0xf) | (flags & 0xf0))
#define GDT_BASE_HIGH(base) ((base >> 24) & 0xff)
#define GDT_ENTRY(base, limit, access, flags)                                                                      \
    {                                                                                                              \
        GDT_LIMIT_LOW(limit), GDT_BASE_LOW(base), GDT_BASE_MIDDLE(base), access, GDT_FLAGS_LIMIT_HI(limit, flags), \
            GDT_BASE_HIGH(base)                                                                                    \
    }

typedef struct {
    uint16_t LimitLow;
    uint16_t BaseLow;
    uint8_t BaseMiddle;
    uint8_t Access;
    uint8_t LimitHi_Flags;
    uint8_t BaseHigh;
} __attribute__((packed)) gdt_entry_t;

// GDT has segments for 16, 32, and 64bit due to limeine requirments

typedef struct {
    gdt_entry_t null;
    gdt_entry_t real_cs;
    gdt_entry_t real_ds;
    gdt_entry_t protected_cs;
    gdt_entry_t protected_ds;
    gdt_entry_t long_cs;
    gdt_entry_t long_ds;
} __attribute__((packed)) gdt_t;

typedef struct {
    uint16_t Limit;   // sizeof(gdt) - 1
    uint64_t Offset;  // address of GDT
} __attribute__((packed)) gdt_descriptor_t;

extern gdt_t gdt_table;
extern gdt_descriptor_t gdt_descriptor;
#endif

void load_gdt(gdt_descriptor_t*);