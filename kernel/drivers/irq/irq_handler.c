#include "irq_handler.h"

#define INTERRUPT_HANDLER(x, y) x##y

struct int_frame;
static uint8_t vectors[32];

__attribute__((interrupt))
void interrupt_handler_0(struct int_frame *frame) {
    // char *ptr = (char*)0xB8000;
    // *ptr = 'X';
}

__attribute__((interrupt))
void interrupt_handler_1(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_2(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_3(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_4(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_5(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_6(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_7(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_8(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_9(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_10(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_11(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_12(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_13(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_14(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_15(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_16(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_17(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_18(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_19(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_20(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_21(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_22(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_23(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_24(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_25(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_26(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_27(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_28(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_29(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_30(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_31(struct int_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void interrupt_handler_32(struct int_frame *frame) {
	// do nothing;
}

void idt_init(void) {
    _idtr_desc.offset = (u32ptr_t)&idt[0];
    _idtr_desc.size = (uint16_t)sizeof(struct interrupt_entry) * IDT_ENTRIES_MAX - 1;
    uint8_t vector;

    for (vector = 0; vector < 32; vector++) {
        idt_create_gate(vector, INTERRUPT_HANDLER(interrupt_handler_, 1), 0x8E);
        vectors[vector] = 1;
    }
 
    __asm__ volatile (
        "lidt %0" :
        : "m"(_idtr_desc)
    );
    __asm__ volatile ("sti");
}
