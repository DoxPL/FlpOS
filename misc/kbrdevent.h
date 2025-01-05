#include "types.h"

typedef enum {
    STD_KEY_EVENT,
    SPL_KEY_EVENT
} KeyEventType;

typedef struct key_event_entry_s {
    KeyEventType event_type;
    uint8_t payload;
} key_event_entry_t;
