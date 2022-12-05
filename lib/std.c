#include "std.h"

static int32_t pow(uint32_t base, uint8_t exponent) {
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

void itoa(uint32_t number, string array) {
	uint8_t index = digits_count(number);

	while(index--) {
		array[index] = (number % 10) + 0x30;
		number /= 10;
	}
}

char *mset(uint8_t* mem_ptr, uint8_t value, uint32_t bytes_count) {
	if (mem_ptr == NULL) {
		goto mset_exit;
	}
	uint32_t index;
	for (index = 0; index < bytes_count; index++) {
		mem_ptr[index] = value;
	}
	mset_exit:
	return mem_ptr;
}

char *mcpy(char *target, const char *source, uint32_t bytes_count) {
	uint32_t byte_index = 0U;
	char *target_addr = NULL;
	while (byte_index < bytes_count) {
		target[byte_index] = source[byte_index++];
	}
	return target_addr;
}

char ascii_val(char num) {
	return num + 0x30;
}
