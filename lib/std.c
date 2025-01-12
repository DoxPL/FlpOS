#include "sys_io.h"
#include "std.h"
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

int8_t ascii_val(int8_t num) {
    return num + 0x30;
}

void putchar_c(const uint8_t symbol, color_t color) {
    uint16_t char_data = 0U;
    switch(symbol) {
        case '\0':
            break;
        case '\n':
        case '\t':
        case '\b':
            write(symbol);
            break;
        default:
            char_data = (color << 8) | symbol;
            write(char_data);
            break;
    }
}

void puts_c(const int8_t *s, color_t color) {
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

void printstr(const int8_t *s, ...) {
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

uint8_t kbrd_getkey(void) {
    key_event_entry_t kbrd_event;
    read_key(&kbrd_event);
    return kbrd_event.payload;
}

void tty_ctest(void) {
    uint8_t buff[VGA_MATRIX_WIDTH + 1];
    buff[VGA_MATRIX_WIDTH] = '\0';
    uint16_t cnum, color;
    for (cnum = 0; cnum < VGA_MATRIX_WIDTH; cnum++) {
        buff[cnum] = 0xDB;
    }
    for (color = 1; color < 16; color++) {
        puts_c(buff, color);
    }
}
