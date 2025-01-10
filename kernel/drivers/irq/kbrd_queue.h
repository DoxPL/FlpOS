#include "types.h"
#include "kbrdevent.h"
#define KBRD_BUFF_SIZE 64

typedef struct key_event_queue_s {
    key_event_entry_t kbrd_buffer[KBRD_BUFF_SIZE];
    int8_t front_event;
    int8_t rear_event;
    uint8_t size;
} key_event_queue_t;

void kbrd_queue_init(key_event_queue_t*);
bool_t kbrd_queue_is_full(key_event_queue_t*);
bool_t kbrd_queue_is_empty(key_event_queue_t*);
void kbrd_queue_enqueue(key_event_queue_t*, key_event_entry_t);
void kbrd_queue_dequeue(key_event_queue_t*, key_event_entry_t*);
