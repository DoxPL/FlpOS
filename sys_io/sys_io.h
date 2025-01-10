#include "types.h"
#include "kbrdevent.h"

#define SYSCALL_INTERRUPT 0x28
#define SYSCALL_WRITE 0x1
#define SYSCALL_READ 0x2

uint32_t write(uint32_t);
void read_key(key_event_entry_t*);
