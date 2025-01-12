/* OS kernel code */
#include <stdarg.h>
#include "lib/std.h"
#include "irq/pic_8259.h"
#include "irq/irq_handler.h"
#include "cli.h"

void main(void) {
    PIC_remap(PIC_NEW_MASTER_OFFSET, PIC_NEW_SLAVE_OFFSET);
    idt_init();
    create_kbrd_queue();

    /* Disable devices */
    outb(0x60, 0xAD);
    outb(0x60, 0xA7);

    tty_ctest();
    kputs("Kernel ready!\n");
    create_cli();

    for(;;) {
        asm("hlt");
    }
}
