#include "kbrd_queue.h"

void kbrd_queue_init(key_event_queue_t *queue) {
    queue->front_event = 0;
    queue->rear_event = 0;
    queue->size = 0;
}

bool_t kbrd_queue_is_full(key_event_queue_t *queue) {
    return queue->size == KBRD_BUFF_SIZE;
}

bool_t kbrd_queue_is_empty(key_event_queue_t *queue) {
    return queue->size == 0;
}

void kbrd_queue_enqueue(key_event_queue_t *queue, key_event_entry_t event) {
    if (!kbrd_queue_is_full(queue)) {
        queue->rear_event = (queue->front_event + queue->size) % KBRD_BUFF_SIZE;
        queue->kbrd_buffer[queue->rear_event].event_type = event.event_type;
        queue->kbrd_buffer[queue->rear_event].payload = event.payload;
        queue->size++;
    }
}

void kbrd_queue_dequeue(key_event_queue_t *queue, key_event_entry_t *out_entry) {
    out_entry->event_type = queue->kbrd_buffer[queue->front_event].event_type;
    out_entry->payload = queue->kbrd_buffer[queue->front_event].payload;
    queue->front_event = (queue->front_event + 1) % KBRD_BUFF_SIZE;
    queue->size--;
}
