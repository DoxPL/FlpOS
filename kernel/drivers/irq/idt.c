#include "idt.h"

__attribute__((aligned(0x10))) 
struct interrupt_entry idt[IDT_ENTRIES_MAX];
struct idtr_desc _idtr_desc;

void idt_create_gate(uint8_t index, void* address, uint8_t flags) {
    struct interrupt_entry *desc = &idt[index];
 
    desc->offset_1 = (uint32_t)address & 0xFFFF;
    desc->selector = 0x08; // kernel offset
    desc->attributes = flags;
    desc->offset_2 = (uint32_t)address >> 16;
}
