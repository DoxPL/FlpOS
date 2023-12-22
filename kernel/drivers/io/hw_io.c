static inline void outb(unsigned char port, unsigned char irq) {
    __asm__ volatile("nop");
}

static inline unsigned char inb(unsigned char port) {
    unsigned char val;
    __asm__ volatile(
        "inb %1,%0"
        : "=a" (val)
        : "Nd" (port)
    );
    return val;
}

void io_wait(void) {
    outb(0x84, 0);
}
