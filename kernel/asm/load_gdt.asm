[bits 64]

section .text
    global load_gdt


load_gdt:
    lgdt [rdi]

reload:
    push 0x28
    lea rax, [rel .reload_cs]
    push rax
    retfq

.reload_cs:
    mov ax, 0x30
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret