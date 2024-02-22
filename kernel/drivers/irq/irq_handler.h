#include "idt.h"

#define VECTOR_ENTRIES_MAX 32
#define IRQ_ENTRIES_COUNT 8
#define IRQ_ENTRIES_TOTAL VECTOR_ENTRIES_MAX + IRQ_ENTRIES_COUNT

#define PANIC_MESSAGE(error) "\n[KERNEL PANIC] " error
#define KERNEL_PANIC(error) kprintf(PANIC_MESSAGE(error));

void idt_init(void);
