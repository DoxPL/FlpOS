#include "irq_handler.h"
#include "pic_8259.h"
#include "kbrd_queue.h"
#include "keyboard.h"
#include "hw_io.h"
#include "vga_generic.h"
#include "std.h"

#define ASCII_ALNUM_KEY(value, offset) (key = value + offset)

struct interrupt_frame
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t eip;
    uint32_t cs;
    uint32_t flags;
    uint32_t sp;
    uint32_t ss;
};

static uint8_t vectors[IRQ_ENTRIES_TOTAL];
static key_event_queue_t kbrd_queue;

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
    KERNEL_PANIC("Control Protection Exception");
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
    CursorKey cursor_key = KEY_CURSOR_UNUSED;
    key_event_entry_t kbrd_event = { 0, 0 };
    uint8_t scan_code = inb(0x60);
    uint8_t key = 0U;

    static SpecialKeyEvent spl_key_event = KEY_SPECIAL_KEY_IDLE;
    static bool_t capslock_active = false;
    static bool_t modifier_key = false;
    static uint8_t offset = 0x20;

    (void) cursor_key;

    if (spl_key_event == KEY_SPECIAL_KEY_IDLE && \
        scan_code == KEY_SPECIAL_KEY) {
        spl_key_event = KEY_SPECIAL_KEY_FIRST_E0;
    } else if (spl_key_event != KEY_SPECIAL_KEY_IDLE) {
        /* State machine for handling special keys */
        switch(spl_key_event) {
            case KEY_SPECIAL_KEY_FIRST_E0:
                spl_key_event = KEY_SPECIAL_KEY_PRESSED;
                kbrd_event.event_type = SPL_KEY_EVENT;
                kbrd_event.payload = scan_code;
                break;
            case KEY_SPECIAL_KEY_PRESSED:
                if (scan_code == KEY_SPECIAL_KEY) {
                    spl_key_event = KEY_SPECIAL_KEY_SECOND_E0;
                }
                break;
            case KEY_SPECIAL_KEY_SECOND_E0:
                spl_key_event = KEY_SPECIAL_KEY_IDLE;
                break;
            default:
                spl_key_event = KEY_SPECIAL_KEY_IDLE;
                break;
        }
    } else {
        switch (scan_code) {
            case KEY_ESCAPE_PRESSED:
                break;
            case KEY_Q_PRESSED:
                ASCII_ALNUM_KEY(0x51, offset);
                break;
            case KEY_W_PRESSED:
                ASCII_ALNUM_KEY(0x57, offset);
                break;
            case KEY_E_PRESSED:
                ASCII_ALNUM_KEY(0x45, offset);
                break;
            case KEY_R_PRESSED:
                ASCII_ALNUM_KEY(0x52, offset);
                break;
            case KEY_T_PRESSED:
                ASCII_ALNUM_KEY(0x54, offset);
                break;
            case KEY_Y_PRESSED:
                ASCII_ALNUM_KEY(0x59, offset);
                break;
            case KEY_U_PRESSED:
                ASCII_ALNUM_KEY(0x55, offset);
                break;
            case KEY_I_PRESSED:
                ASCII_ALNUM_KEY(0x49, offset);
                break;
            case KEY_O_PRESSED:
                ASCII_ALNUM_KEY(0x4F, offset);
                break;
            case KEY_P_PRESSED:
                ASCII_ALNUM_KEY(0x50, offset);
                break;
            case KEY_A_PRESSED:
                ASCII_ALNUM_KEY(0x41, offset);
                break;
            case KEY_S_PRESSED:
                ASCII_ALNUM_KEY(0x53, offset);
                break;
            case KEY_D_PRESSED:
                ASCII_ALNUM_KEY(0x44, offset);
                break;
            case KEY_F_PRESSED:
                ASCII_ALNUM_KEY(0x46, offset);
                break;
            case KEY_G_PRESSED:
                ASCII_ALNUM_KEY(0x47, offset);
                break;
            case KEY_H_PRESSED:
                ASCII_ALNUM_KEY(0x48, offset);
                break;
            case KEY_J_PRESSED:
                ASCII_ALNUM_KEY(0x4A, offset);
                break;
            case KEY_K_PRESSED:
                ASCII_ALNUM_KEY(0x4B, offset);
                break;
            case KEY_L_PRESSED:
                ASCII_ALNUM_KEY(0x4C, offset);
                break;
            case KEY_Z_PRESSED:
                ASCII_ALNUM_KEY(0x5A, offset);
                break;
            case KEY_X_PRESSED:
                ASCII_ALNUM_KEY(0x58, offset);
                break;
            case KEY_C_PRESSED:
                ASCII_ALNUM_KEY(0x43, offset);
                break;
            case KEY_V_PRESSED:
                ASCII_ALNUM_KEY(0x56, offset);
                break;
            case KEY_B_PRESSED:
                ASCII_ALNUM_KEY(0x42, offset);
                break;
            case KEY_N_PRESSED:
                ASCII_ALNUM_KEY(0x4E, offset);
                break;
            case KEY_M_PRESSED:
                ASCII_ALNUM_KEY(0x4D, offset);
                break;
            case KEY_KPD_ZERO_PRESSED:
                key = 0x30;
                break;
            case KEY_ZERO_PRESSED:
                key = modifier_key ? 0x29 : 0x30;
                break;
            case KEY_KPD_ONE_PRESSED:
                key = 0x31;
                break;
            case KEY_ONE_PRESSED:
                key = modifier_key ? 0x21 : 0x31;
                break;
            case KEY_KPD_TWO_PRESSED:
                key = 0x32;
                break;
            case KEY_TWO_PRESSED:
                key = modifier_key ? 0x40 : 0x32;
                break;
            case KEY_KPD_THREE_PRESSED:
                key = 0x33;
                break;
            case KEY_THREE_PRESSED:
                key = modifier_key ? 0x23 : 0x33;
                break;
            case KEY_KPD_FOUR_PRESSED:
                key = 0x34;
                break;
            case KEY_FOUR_PRESSED:
                key = modifier_key ? 0x24 : 0x34;
                break;
            case KEY_KPD_FIVE_PRESSED:
                key = 0x35;
                break;
            case KEY_FIVE_PRESSED:
                key = modifier_key ? 0x25 : 0x35;
                break;
            case KEY_KPD_SIX_PRESSED:
                key = 0x36;
                break;
            case KEY_SIX_PRESSED:
                key = modifier_key ? 0x5E : 0x36;
                break;
            case KEY_KPD_SEVEN_PRESSED:
                key = 0x37;
                break;
            case KEY_SEVEN_PRESSED:
                key = modifier_key ? 0x26 : 0x37;
                break;
            case KEY_KPD_EIGHT_PRESSED:
                key = 0x38;
                break;
            case KEY_EIGHT_PRESSED:
                key = modifier_key ? 0x2A : 0x38;
                break;
            case KEY_KPD_NINE_PRESSED:
                key = 0x39;
                break;
            case KEY_NINE_PRESSED:
                key = modifier_key ? 0x28 : 0x39;
                break;
            case KEY_SPACE_PRESSED:
                key = 0x20;
                break;
            case KEY_ENTER_PRESSED:
                putchar('\n');
                break;
            case KEY_DOT_PRESSED:
                key = modifier_key ? 0x3E : 0x2E;
                break;
            case KEY_COMMA_PRESSED:
                key = modifier_key ? 0x3C : 0x2C;
                break;
            case KEY_CAPSLOCK_PRESSED:
                capslock_active = true;
            case KEY_LSHIFT_PRESSED:
            case KEY_RSHIFT_PRESSED:
                modifier_key = true;
                offset = 0U;
                break;
            case KEY_CAPSLOCK_RELEASED:
                capslock_active = false;
                offset = 0x20;
            case KEY_LSHIFT_RELEASED:
            case KEY_RSHIFT_RELEASED:
                if (!capslock_active) {
                    offset = 0x20;
                }
                modifier_key = false;
                break;
            case KEY_BACKSPACE_PRESSED:
                putchar('\b');
                break;
            case KEY_SLASH_PRESSED:
                key = modifier_key ? 0x3F : 0x2F;
                break;
            case KEY_BACKSLASH_PRESSED:
                key = modifier_key ? 0x7C : 0x5C;
                break;
            case KEY_BACKTICK_PRESSED:
                key = modifier_key ? 0x7E : 0x60;
                break;
            case KEY_SQUOTE_PRESSED:
                key = modifier_key ? 0x22 : 0x27;
                break;
            case KEY_DASH_PRESSED:
                key = modifier_key ? 0x5F : 0x2D;
                break;
            case KEY_EQSIGN_PRESSED:
                key = modifier_key ? 0x2B : 0x3D;
                break;
            case KEY_SEMICOLON_PRESSED:
                key = modifier_key ? 0x3A : 0x3B;
                break;
            case KEY_LBRACKET_PRESSED:
                key = modifier_key ? 0x7B : 0x5B;
                break;
            case KEY_RBRACKET_PRESSED:
                key = modifier_key ? 0x7D : 0x5D;
                break;
            case KEY_KPD_ASTERISK_PRESSED:
                key = 0x2A;
                break;
            case KEY_TAB_PRESSED:
                key = '\t';
                break;
            default:
                break;
        }
    }

    if (key > 0) {
        kbrd_event.event_type = STD_KEY_EVENT;
        kbrd_event.payload = key;
    }

    if (kbrd_event.payload > 0) {
        kbrd_queue_enqueue(&kbrd_queue, kbrd_event);
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

__attribute__((interrupt))
void interrupt_handler_8(struct interrupt_frame *frame) {
    /* Syscall handler */
    key_event_entry_t kbrd_event = { 0, 0 };
    uint32_t syscall_id;
    uint32_t *val_user = NULL;

    __asm__ volatile(
        "movl %%ebx, %0\n"
        "movl %%ecx, %1\n"
        : "=r"(syscall_id),
        "=r"(val_user)
    );

    switch (syscall_id) {
        case SYSCALL_WRITE:
            if (val_user != NULL) {
                vga_write_user_data(*val_user, 1);
            }
            break;
        case SYSCALL_READ:
            if (!kbrd_queue_is_empty(&kbrd_queue)) {
                kbrd_queue_dequeue(&kbrd_queue, &kbrd_event);
                if (val_user != NULL) {
                    *val_user = ((kbrd_event.event_type << 8) | \
                        kbrd_event.payload) & 0xFFFF;
                }
            }
            break;
        default:
            break;
    }

    PIC_8259_send_EOI(0x28);
}

void (*interrupt_handler_array[IRQ_ENTRIES_TOTAL])() = {
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
    interrupt_handler_7,
    interrupt_handler_8
};

void idt_init(void) {
    _idtr_desc.offset = (uint32_t)&idt[0]; // u32ptr_t
    _idtr_desc.size = (uint16_t)sizeof(struct interrupt_entry) * IDT_ENTRIES_MAX - 1;
    uint8_t vector;

    for (vector = 0; vector < IRQ_ENTRIES_TOTAL; vector++) {
        idt_create_gate(vector, interrupt_handler_array[vector], 0x8E);
        vectors[vector] = 1;
    }

    __asm__ volatile ("lidt %0" : : "m"(_idtr_desc));
    __asm__ volatile ("sti");
}

void create_kbrd_queue(void) {
    kbrd_queue_init(&kbrd_queue);
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
