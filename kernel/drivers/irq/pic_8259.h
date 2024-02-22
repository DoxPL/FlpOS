#include "../hw_io/hw_io.h"

#define PIC_NEW_MASTER_OFFSET 0x20
#define PIC_NEW_SLAVE_OFFSET 0x28

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

void PIC_8259_send_EOI(enum Std_IRQ irq);
void PIC_remap(uint32_t, uint32_t);
