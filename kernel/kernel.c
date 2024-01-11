/* OS kernel code */
#include <stdarg.h>
#include "lib/std.h"
#include "gfx/vga_generic.h"
#include "irq/pic_8259.h"
#include "irq/irq_handler.h"

static void putchar_c(const uint8_t symbol, color_t color);
static void kputs_c(const char *s, color_t color);

#define putchar(str) putchar_c(str, 0x0F);
#define kputs(str) kputs_c(str, 0x0F);

static void write_number(int value) {
	uint8_t value_str[INT_DIGITS_MAX];
	itoa(value, value_str);
	uint8_t *symbol_ptr = (uint8_t*) value_str;
	while(*symbol_ptr != '\0') {
		putchar(*symbol_ptr++);
	}
}

static void kprintf(const char *s, ...) {
    va_list arg_list;
	va_start(arg_list, s);
    for (const char *c = s; *c != '\0'; c++) {
		char symbol = *c;
        if (symbol == '%') {
			symbol = *(++c);
            switch(symbol) {
				case 'd':
					int value = va_arg(arg_list, int);
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

static void kputs_c(const char *s, color_t color) {
	for (const char *c = s; *c != '\0'; c++) {
		putchar_c(*c, color);
	}
}

static void putchar_c(const uint8_t symbol, color_t color) {
	uint16_t char_data = 0U;
	uint8_t bytes_in_row = 0U;
	switch(symbol) {
		case '\0':
			break;
		case '\n':
			bytes_in_row = (vga_get_addr() - VIDEO_MEMORY) % (VGA_MATRIX_WIDTH << 1);
			vga_set_addr(vga_get_addr() + ((VGA_MATRIX_WIDTH << 1) - bytes_in_row));
			break;
		case '\t':
			vga_set_addr(vga_get_addr() + 0x8);
			break;
		default:
			char_data = (color << 8) | symbol;
			vga_write_word(&char_data);
			break;
	}
}

static void tty_ctest(void) {
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

void main(void) {
	tty_ctest();
	kputs("Kernel ready!");
	kputs("\nHello from kernel");
	PIC_remap(1, 2);
	idt_init();

	return;
}
