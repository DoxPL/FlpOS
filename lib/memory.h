#include "types.h"

uint8_t *mset(uint8_t*, uint8_t, uint32_t);
uint8_t *mset16(uint8_t*, uint16_t, uint32_t);
uint8_t *mcpy(int8_t*, const int8_t*, uint32_t);
int8_t stringcmp(const char *, const char *, size_t);
uint32_t stringlen(const char *);
char *stringtok(char *, const char);
