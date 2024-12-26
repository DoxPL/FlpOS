#include "pic_8259.h"

void PIC_8259_send_EOI(enum Std_IRQ irq) {
    /* End of interrupt */
    if (irq >= 8) {
        outb(SLAVE_CMD_IO_PORT, 0x20);
    }
    outb(MASTER_CMD_IO_PORT, 0x20);
}

void PIC_remap(uint32_t m_pic_vec_offset, uint32_t s_pic_vec_offset) {
    uint8_t master_pic_mask;
    uint8_t slave_pic_mask;
    master_pic_mask = inb(MASTER_DATA_IO_PORT);
    slave_pic_mask = inb(SLAVE_DATA_IO_PORT);

    outb(MASTER_CMD_IO_PORT, CMD_PIC_INIT);
    io_wait();
    outb(SLAVE_CMD_IO_PORT, CMD_PIC_INIT);
    io_wait();

    outb(MASTER_DATA_IO_PORT, m_pic_vec_offset);
    io_wait();
    outb(SLAVE_DATA_IO_PORT, s_pic_vec_offset);
    io_wait();

    outb(MASTER_DATA_IO_PORT, CMD_PIC_SLAVE_AT_IRQ2);
    io_wait();
    outb(SLAVE_DATA_IO_PORT, CMD_PIC_CASCADE_IDENTITY);
    io_wait();

    outb(MASTER_DATA_IO_PORT, CMD_PIC_SET_8086_MODE);
    io_wait();
    outb(SLAVE_DATA_IO_PORT, CMD_PIC_SET_8086_MODE);
    io_wait();

    outb(MASTER_DATA_IO_PORT, master_pic_mask);
    outb(SLAVE_DATA_IO_PORT, slave_pic_mask);
}
