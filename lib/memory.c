#include "memory.h"

uint8_t *mset(uint8_t *mem_ptr, uint8_t value, uint32_t bytes_count) {
    if (mem_ptr != NULL) {
        uint32_t index;
        for (index = 0; index < bytes_count; index++) {
            mem_ptr[index] = value;
        }
    }
    return mem_ptr;
}

uint8_t *mset16(uint8_t *mem_ptr, uint16_t value, uint32_t count) {
    if (mem_ptr != NULL) {
        uint32_t index;
        for (index = 0; index < count; index+=2) {
            mem_ptr[index] = value;
        }
    }
    return mem_ptr;
}

uint8_t *mcpy(int8_t *target, const int8_t *source, uint32_t bytes_count) {
    uint32_t byte_index = 0U;
    int8_t *target_addr = NULL;
    while (byte_index < bytes_count) {
        target[byte_index] = source[byte_index++];
    }
    return target_addr;
}
