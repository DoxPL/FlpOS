#include "hw_io.h"

inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile(
        "outb %0, %1" :
        : "a" (value), "Nd" (port)
        : "memory"
    );
}

inline unsigned char inb(unsigned char port) {
    unsigned char val;
    __asm__ volatile(
        "inb %1,%0"
        : "=a" (val)
        : "Nd" (port)
    );
    return val;
}

inline void io_wait(void) {
    outb(0x84, 0);
}
