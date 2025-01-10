#include "types.h"

#define IDT_ENTRIES_MAX 256
#define SYSCALL_WRITE 0x1
#define SYSCALL_READ 0x2

typedef struct interrupt_entry {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero_byte;
    uint8_t attributes;
    uint16_t offset_2;
} __attribute__((packed)) interrupt_entry;

typedef struct {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idtr_desc;

__attribute__((aligned(0x10))) 
extern interrupt_entry idt[IDT_ENTRIES_MAX];
extern idtr_desc _idtr_desc;

void idt_create_gate(uint8_t, void*, uint8_t);
