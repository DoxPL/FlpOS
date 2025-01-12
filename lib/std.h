#include "types.h"

#define INT_DIGITS_MAX 12
#define VGA_MATRIX_WIDTH 80

int32_t atoi(const string);
void itoa(int32_t, uint8_t[]);
int8_t ascii_val(int8_t);

void putchar_c(const uint8_t, color_t);
void puts_c(const int8_t *, color_t);
void write_number(int32_t);
void _printf(const int8_t *, ...);
uint8_t kbrd_getkey(void);
void tty_ctest(void);

extern void vga_sync_cursor(void);

#define putchar(str) putchar_c(str, VGA_CWHITE);
#define kputs(str) puts_c(str, VGA_CWHITE);
