#ifndef HW_IO_HEADER
#define HW_IO_HEADER

#define MASTER_CMD_IO_PORT 0x20
#define MASTER_DATA_IO_PORT 0x21
#define SLAVE_CMD_IO_PORT 0xA0
#define SLAVE_DATA_IO_PORT 0xA1

#define PIC_MASTER_CHIP 0x20
#define PIC_SLAVE_CHIP 0xA0

#define CMD_PIC_INIT 0x11
#define CMD_PIC_SLAVE_AT_IRQ2 0x4
#define CMD_PIC_CASCADE_IDENTITY 0x2
#define CMD_PIC_SET_8086_MODE 0x1

enum Std_IRQ {
    IRQ_PROG_INT_TIMER = 0,
    IRQ_KEYBOARD_INT,
    IRQ_CASCADE,
    IRQ_COM2,
    IRQ_COM1,
    IRQ_LPT2,
    IRQ_FLOPPY_DISK,
    IRQ_LPT1,
    IRQ_CMOS_RTC,
    IRQ_FFP1,
    IRQ_FFP2,
    IRQ_FFP3,
    IRQ_PS2_MOUSE,
    IRQ_FPU,
    IRQ_PRIM_ATA_HD,
    IRQ_SEC_ATA_HD
};

static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile(
        "outb %0, %1" :
        : "a" (value), "Nd" (port)
        : "memory"
    );
}

static inline unsigned char inb(unsigned short port) {
    unsigned char val;
    __asm__ volatile(
        "inb %1,%0"
        : "=a" (val)
        : "Nd" (port)
    );
    return val;
}

static inline void io_wait(void) {
    outb(0x84, 0);
}

#endif
