/* OS kernel code */
#include <stdarg.h>
#include "lib/std.h"
#include "gfx/vga_generic.h"
#include "irq/pic_8259.h"
#include "irq/irq_handler.h"

void main(void) {
    tty_ctest();
    kputs("Kernel ready!");
    kputs("\nHello from kernel");
    PIC_remap(PIC_NEW_MASTER_OFFSET, PIC_NEW_SLAVE_OFFSET);
    idt_init();

    /* Disable devices */
    outb(0x60, 0xAD);
    outb(0x60, 0xA7);

    for(;;) {
        asm("hlt");
    }
}
