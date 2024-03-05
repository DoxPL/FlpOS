#include "types.h"

#define INT_DIGITS_MAX 12

int32_t atoi(const string);
void itoa(int32_t, uint8_t[]);
uint8_t *mset(uint8_t*, uint8_t, uint32_t);
uint8_t *mset16(uint8_t*, uint16_t, uint32_t);
uint8_t *mcpy(int8_t *, const int8_t *, uint32_t);
int8_t ascii_val(int8_t);

void putchar_c(const uint8_t, color_t);
void kputs_c(const int8_t *, color_t);
void write_number(int32_t);
void kprintf(const int8_t *, ...);
void tty_ctest(void);

#define putchar(str) putchar_c(str, VGA_CWHITE);
#define kputs(str) kputs_c(str, VGA_CWHITE);
