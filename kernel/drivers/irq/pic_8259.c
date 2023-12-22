#include "hw_io.h"

#define MASTER_CMD_IO_PORT 0x20
#define MASTER_DATA_IO_PORT 0x21
#define SLAVE_CMD_IO_PORT 0xA0
#define SLAVE_DATA_IO_PORT 0xA1

#define PIC_MASTER_CHIP 0x20
#define PIC_SLAVE_CHIP 0xA0

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

void PIC_8259_send_EOI(enum Std_IRQ irq) {
    /* End of interrupt */
    outb(MASTER_CMD_IO_PORT, irq);
}
