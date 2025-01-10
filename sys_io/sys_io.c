#include "sys_io.h"

uint32_t write(uint32_t val_user) {
    uint32_t bytes_written;
    __asm__ volatile(
        "int %1"
        : "=a" (bytes_written)
        : "i" (SYSCALL_INTERRUPT),
        "b" (SYSCALL_WRITE),
        "c" (&val_user)
        : "cc", "memory"
    );
    return bytes_written;
}

void read_key(key_event_entry_t *key_event) {
    uint32_t val_kernel = 0U;
    uint8_t payload = 0U;

    while (1) {
        __asm__ volatile(
            "int %0"
            : : "i" (SYSCALL_INTERRUPT),
            "b" (SYSCALL_READ),
            "c" (&val_kernel)
        );

        if (val_kernel > 0 && key_event != NULL) {
            key_event->event_type = (uint8_t)(val_kernel >> 8) & 0xFF;
            key_event->payload = (uint8_t)(val_kernel & 0xFF);
            break;
        }
    }
}
