#include "irq_handler.h"

struct interrupt_frame
{
	uint32_t ip;
	uint32_t cs;
	uint32_t flags;
	uint32_t sp;
	uint32_t ss;
};

static uint8_t vectors[VECTOR_ENTRIES_MAX];

__attribute__((interrupt))
void exception_handler_0(struct interrupt_frame *frame) {
	u16ptr_t *ptr = (char*)0xB8000;
	*ptr = (0x0F << 8) | 0x41;
}

__attribute__((interrupt))
void exception_handler_1(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_2(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_3(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_4(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_5(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_6(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_7(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_8(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_9(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_10(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_11(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_12(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_13(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_14(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_15(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_16(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_17(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_18(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_19(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_20(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_21(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_22(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_23(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_24(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_25(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_26(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_27(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_28(struct interrupt_frame *frame) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_29(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_30(struct interrupt_frame *frame, uword_t err_code) {
	// do nothing;
}

__attribute__((interrupt))
void exception_handler_31(struct interrupt_frame *frame) {
	// do nothing;
}

void (*exception_handler_array[32])() = {
	exception_handler_0,
	exception_handler_1,
	exception_handler_2,
	exception_handler_3,
	exception_handler_4,
	exception_handler_5,
	exception_handler_6,
	exception_handler_7,
	exception_handler_8,
	exception_handler_9,
	exception_handler_10,
	exception_handler_11,
	exception_handler_12,
	exception_handler_13,
	exception_handler_14,
	exception_handler_15,
	exception_handler_16,
	exception_handler_17,
	exception_handler_18,
	exception_handler_19,
	exception_handler_20,
	exception_handler_21,
	exception_handler_22,
	exception_handler_23,
	exception_handler_24,
	exception_handler_25,
	exception_handler_26,
	exception_handler_27,
	exception_handler_28,
	exception_handler_29,
	exception_handler_30,
	exception_handler_31
};

void idt_init(void) {
    _idtr_desc.offset = (u32ptr_t)&idt[0]; // u32ptr_t
    _idtr_desc.size = (uint16_t)sizeof(struct interrupt_entry) * IDT_ENTRIES_MAX - 1;
    uint8_t vector;

    for (vector = 0; vector < VECTOR_ENTRIES_MAX; vector++) {
        idt_create_gate(vector, exception_handler_array[vector], 0x8E);
        vectors[vector] = 1;
    }

    __asm__ volatile ("lidt %0" : : "m"(_idtr_desc));
    __asm__ volatile ("sti");
	int x = 1 / 0;
}
