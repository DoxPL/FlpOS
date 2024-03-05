#include "std.h"
#include "vga_generic.h"
#include <stdarg.h>

static int32_t mpow(uint32_t base, uint8_t exponent) {
    int32_t value = 1;
    uint8_t index;

    for (index = 0; index < exponent; index++) {
        value *= base;
    }

    return value;
}

static uint8_t digits_count(uint32_t number) {
    uint8_t count = 1U;
    while (number /= 10) {
        count++;
    }
    return count;
}

int32_t atoi(const string array) {
    int32_t value = 0;

    uint8_t *buff_ptr = array;
    int8_t sign = (*buff_ptr == '-' ? -1 : 1);

    if (sign == -1) { buff_ptr++; }

    while (*buff_ptr != '\0') {
        value = 10 * value + *buff_ptr - 0x30;
        buff_ptr++;
    }

    return value * sign;
}

void itoa(int32_t number, uint8_t array[]) {
    uint8_t i, digits, subtrahend = 0U;
    if (number < 0) {
        array[digits++] = '-';
        number *= -1;
        i = 1U;
    } else {
        subtrahend = 1U;
    }

    do {
        array[digits] = (number % 10) + 0x30;
        number /= 10;
        digits++;
    } while (number);
    
    for (; i < digits / 2; i++) {
        uint8_t tmp = array[i];
        array[i] = array[digits - i - subtrahend];
        array[digits - i - subtrahend] = tmp;
    }

    array[digits] = '\0';
}

uint8_t *mset(uint8_t* mem_ptr, uint8_t value, uint32_t bytes_count) {
    if (mem_ptr != NULL) {
        uint32_t index;
        for (index = 0; index < bytes_count; index++) {
            mem_ptr[index] = value;
        }
    }
    return mem_ptr;
}

uint8_t *mset16(uint8_t* mem_ptr, uint16_t value, uint32_t count) {
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

int8_t ascii_val(int8_t num) {
    return num + 0x30;
}

void putchar_c(const uint8_t symbol, color_t color) {
    uint16_t char_data = 0U;
    switch(symbol) {
        case '\0':
            break;
        case '\n':
            cursor_down();
            break;
        case '\t':
            vga_set_addr(vga_get_addr() + 0x8);
            break;
        case '\b':
            vga_set_addr(vga_get_addr() - 0x2);
            char_data = (color << 8) | 0x20;
            vga_replace_symbol(&char_data);
            break;
        default:
            char_data = (color << 8) | symbol;
            vga_write_word(&char_data);
            break;
    }
}

void kputs_c(const int8_t *s, color_t color) {
    for (const int8_t *c = s; *c != '\0'; c++) {
        putchar_c(*c, color);
    }
}

void write_number(int32_t value) {
    uint8_t value_str[INT_DIGITS_MAX];
    itoa(value, value_str);
    uint8_t *symbol_ptr = (uint8_t*) value_str;
    while(*symbol_ptr != '\0') {
        putchar(*symbol_ptr++);
    }
}

void kprintf(const int8_t *s, ...) {
    va_list arg_list;
    va_start(arg_list, s);
    for (const int8_t *c = s; *c != '\0'; c++) {
        int8_t symbol = *c;
        if (symbol == '%') {
            symbol = *(++c);
            switch(symbol) {
                case 'd':
                    int32_t value = va_arg(arg_list, int32_t);
                    write_number(value);
                    break;
                case 's':
                    break;
                default:
                    break;
            }
        } else {
            putchar(symbol);
        }
    }
    va_end(arg_list);
}

void tty_ctest(void) {
    uint8_t buff[VGA_MATRIX_WIDTH + 1];
    buff[VGA_MATRIX_WIDTH] = '\0';
    uint16_t cnum, color;
    for (cnum = 0; cnum < VGA_MATRIX_WIDTH; cnum++) {
        buff[cnum] = '#'; //0xDB;
    }
    for (color = 1; color < 16; color++) {
        kputs_c(buff, color);
    }
}
