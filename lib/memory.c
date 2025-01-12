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

int8_t stringcmp(const char *first_str, const char *second_str, size_t size) {
    uint8_t i;
    int8_t ret = 0;
    if (first_str == NULL || second_str == NULL) {
        return -1;
    }
    for (i = 0U; i < size; i++) {
        if (first_str[i] != second_str[i]) {
            ret = 1;
            break;
        } else if (first_str[i] == '\0' || second_str[i] == '\0') {
            break;
        }
    }
    return ret;
}

uint32_t stringlen(const char *str) {
    uint32_t str_length = 0U;
    while (*str != '\0') {
        str_length++;
        str++;
    }
    return str_length;
}

char *stringtok(char *str, const char delimiter) {
    static char *ptr = NULL;
    char *init_addr = NULL;
    if (str != NULL) {
        ptr = str;
    }

    if (*ptr == '\0') {
        init_addr = NULL;
    } else {
        init_addr = ptr;
    }

    while(*ptr != '\0') {
        if (*ptr == delimiter) {
            *ptr++ = '\0';
            break;
        }
        ptr++;
    }
    return init_addr;
}
