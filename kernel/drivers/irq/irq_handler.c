#include "irq_handler.h"
#include "pic_8259.h"
#include "keyboard.h"
#include "hw_io.h"
#include "std.h"

struct interrupt_frame
{
    uint32_t ip;
    uint32_t cs;
    uint32_t flags;
    uint32_t sp;
    uint32_t ss;
};

static uint8_t vectors[IRQ_ENTRIES_TOTAL];

__attribute__((interrupt))
void exception_handler_0(struct interrupt_frame *frame) {
    KERNEL_PANIC("Division Error");
}

__attribute__((interrupt))
void exception_handler_1(struct interrupt_frame *frame) {
    KERNEL_PANIC("Debug");
}

__attribute__((interrupt))
void exception_handler_2(struct interrupt_frame *frame) {
    KERNEL_PANIC("Non-maskable Interrupt (NMI)");
}

__attribute__((interrupt))
void exception_handler_3(struct interrupt_frame *frame) {
    KERNEL_PANIC("Breakpoint");
}

__attribute__((interrupt))
void exception_handler_4(struct interrupt_frame *frame) {
    KERNEL_PANIC("Overflow");
}

__attribute__((interrupt))
void exception_handler_5(struct interrupt_frame *frame) {
    KERNEL_PANIC("Bound Range Exceeded");
}

__attribute__((interrupt))
void exception_handler_6(struct interrupt_frame *frame) {
    KERNEL_PANIC("Invalid Opcode");
}

__attribute__((interrupt))
void exception_handler_7(struct interrupt_frame *frame) {
    KERNEL_PANIC("Device not available");
}

__attribute__((interrupt))
void exception_handler_8(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("Double fault");
}

__attribute__((interrupt))
void exception_handler_9(struct interrupt_frame *frame) {
    KERNEL_PANIC("Coprocessor Segment Overrun");
}

__attribute__((interrupt))
void exception_handler_10(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("Invalid TSS");
}

__attribute__((interrupt))
void exception_handler_11(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("Segment not present");
}

__attribute__((interrupt))
void exception_handler_12(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("Stack Segment Fault");
}

__attribute__((interrupt))
void exception_handler_13(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("General Protection Fault");
}

__attribute__((interrupt))
void exception_handler_14(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("Page fault");
}

__attribute__((interrupt))
void exception_handler_15(struct interrupt_frame *frame) {
    KERNEL_PANIC("(Reserved)");
}

__attribute__((interrupt))
void exception_handler_16(struct interrupt_frame *frame) {
    KERNEL_PANIC("x87 Floating-point Exception");
}

__attribute__((interrupt))
void exception_handler_17(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("Alignment Check");
}

__attribute__((interrupt))
void exception_handler_18(struct interrupt_frame *frame) {
    KERNEL_PANIC("Machine Check");
}

__attribute__((interrupt))
void exception_handler_19(struct interrupt_frame *frame) {
    KERNEL_PANIC("SIMD Floating-point Exception");
}

__attribute__((interrupt))
void exception_handler_20(struct interrupt_frame *frame) {
    KERNEL_PANIC("Virtualization Exception");
}

__attribute__((interrupt))
void exception_handler_21(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("Control Protection Exception")
}

__attribute__((interrupt))
void exception_handler_22(struct interrupt_frame *frame) {
    KERNEL_PANIC("(Reserved)");
}

__attribute__((interrupt))
void exception_handler_23(struct interrupt_frame *frame) {
    KERNEL_PANIC("(Reserved)");
}

__attribute__((interrupt))
void exception_handler_24(struct interrupt_frame *frame) {
    KERNEL_PANIC("(Reserved)");
}

__attribute__((interrupt))
void exception_handler_25(struct interrupt_frame *frame) {
    KERNEL_PANIC("(Reserved)");
}

__attribute__((interrupt))
void exception_handler_26(struct interrupt_frame *frame) {
    KERNEL_PANIC("(Reserved)");
}

__attribute__((interrupt))
void exception_handler_27(struct interrupt_frame *frame) {
    KERNEL_PANIC("(Reserved)");
}

__attribute__((interrupt))
void exception_handler_28(struct interrupt_frame *frame) {
    KERNEL_PANIC("Hypervisor Injection Exception");
}

__attribute__((interrupt))
void exception_handler_29(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("VMM Communication Exception");
}

__attribute__((interrupt))
void exception_handler_30(struct interrupt_frame *frame, uword_t err_code) {
    KERNEL_PANIC("Security Exception");
}

__attribute__((interrupt))
void exception_handler_31(struct interrupt_frame *frame) {
    KERNEL_PANIC("(Reserved)");
}

__attribute__((interrupt))
void interrupt_handler_0(struct interrupt_frame *frame) {
    /* 	Programmable Interrupt Timer Interrupt */
    PIC_8259_send_EOI(IRQ_PROG_INT_TIMER);
}

__attribute__((interrupt))
void interrupt_handler_1(struct interrupt_frame *frame) {
    /* 	Keyboard Interrupt */
    uint8_t scan_code = inb(0x60);
    uint8_t key = 0;

    switch (scan_code) {
        case KEY_Q_PRESSED:
            key = 0x51;
            break;
        case KEY_W_PRESSED:
            key = 0x57;
            break;
        case KEY_E_PRESSED:
            key = 0x45;
            break;
        case KEY_R_PRESSED:
            key = 0x52;
            break;
        case KEY_T_PRESSED:
            key = 0x54;
            break;
        case KEY_Y_PRESSED:
            key = 0x59;
            break;
        case KEY_U_PRESSED:
            key = 0x55;
            break;
        case KEY_I_PRESSED:
            key = 0x49;
            break;
        case KEY_O_PRESSED:
            key = 0x4F;
            break;
        case KEY_P_PRESSED:
            key = 0x50;
            break;
        case KEY_A_PRESSED:
            key = 0x41;
            break;
        case KEY_S_PRESSED:
            key = 0x53;
            break;
        case KEY_D_PRESSED:
            key = 0x44;
            break;
        case KEY_F_PRESSED:
            key = 0x46;
            break;
        case KEY_G_PRESSED:
            key = 0x47;
            break;
        case KEY_H_PRESSED:
            key = 0x48;
            break;
        case KEY_J_PRESSED:
            key = 0x4A;
            break;
        case KEY_K_PRESSED:
            key = 0x4B;
            break;
        case KEY_L_PRESSED:
            key = 0x4C;
            break;
        case KEY_Z_PRESSED:
            key = 0x5A;
            break;
        case KEY_X_PRESSED:
            key = 0x58;
            break;
        case KEY_C_PRESSED:
            key = 0x43;
            break;
        case KEY_V_PRESSED:
            key = 0x56;
            break;
        case KEY_B_PRESSED:
            key = 0x42;
            break;
        case KEY_N_PRESSED:
            key = 0x4E;
            break;
        case KEY_M_PRESSED:
            key = 0x4D;
            break;
        case KEY_SPACE_PRESSED:
            key = 0x20;
            break;
        case KEY_DOT_PRESSED:
            break;
        case KEY_COMMA_PRESSED:
            break;
        default:
            break;
    }
    if (key > 0) {
        putchar(key);
    }
    PIC_8259_send_EOI(IRQ_KEYBOARD_INT);
}

__attribute__((interrupt))
void interrupt_handler_2(struct interrupt_frame *frame) {
    /* Cascade */
    PIC_8259_send_EOI(IRQ_CASCADE);
}

__attribute__((interrupt))
void interrupt_handler_3(struct interrupt_frame *frame) {
    /* COM2 */
    PIC_8259_send_EOI(IRQ_COM2);
}

__attribute__((interrupt))
void interrupt_handler_4(struct interrupt_frame *frame) {
    /* COM1 */
    PIC_8259_send_EOI(IRQ_COM1);
}

__attribute__((interrupt))
void interrupt_handler_5(struct interrupt_frame *frame) {
    /* LPT2 */
    PIC_8259_send_EOI(IRQ_LPT2);
}

__attribute__((interrupt))
void interrupt_handler_6(struct interrupt_frame *frame) {
    /* Floppy disk */
    PIC_8259_send_EOI(IRQ_FLOPPY_DISK);
}

__attribute__((interrupt))
void interrupt_handler_7(struct interrupt_frame *frame) {
    /* LPT1 / Spurious IRQ workaround */
    uint8_t irr;
    outb(0x20, 0x0B);
    irr = inb(0x20);
    if (irr & 0x80 > 0) {
        return;
    }
    PIC_8259_send_EOI(IRQ_LPT1);
}

void (*exception_handler_array[IRQ_ENTRIES_TOTAL])() = {
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
    exception_handler_31,
    interrupt_handler_0,
    interrupt_handler_1,
    interrupt_handler_2,
    interrupt_handler_3,
    interrupt_handler_4,
    interrupt_handler_5,
    interrupt_handler_6,
    interrupt_handler_7
};

void idt_init(void) {
    _idtr_desc.offset = (uint32_t)&idt[0]; // u32ptr_t
    _idtr_desc.size = (uint16_t)sizeof(struct interrupt_entry) * IDT_ENTRIES_MAX - 1;
    uint8_t vector;

    for (vector = 0; vector < IRQ_ENTRIES_TOTAL; vector++) {
        idt_create_gate(vector, exception_handler_array[vector], 0x8E);
        vectors[vector] = 1;
    }

    __asm__ volatile ("lidt %0" : : "m"(_idtr_desc));
    __asm__ volatile ("sti");
}

void irq_clear_mask(uint8_t irq_line) {
    uint16_t port;
    uint8_t value;

    if (irq_line < 8) {
        port = MASTER_DATA_IO_PORT;
    } else {
        port = SLAVE_DATA_IO_PORT;
        irq_line -= 8;
    }

    value = inb(port) & ~(1 << irq_line);
    outb(port, value);
}

void irq_set_mask(uint8_t irq_line) {
    uint16_t port;
    uint8_t value;

    if (irq_line < 8) {
        port = MASTER_DATA_IO_PORT;
    } else {
        port = SLAVE_DATA_IO_PORT;
        irq_line -= 8;
    }

    value = inb(port) | (1 << irq_line);
    outb(port, value);
}
