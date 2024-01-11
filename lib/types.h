#pragma once

#define NULL (void*)0
#define true 1
#define false 0

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;
typedef unsigned int* u32ptr_t;
typedef unsigned short* u16ptr_t;
typedef unsigned char* u8ptr_t;
typedef void* vptr_t;
typedef char* string;

typedef struct list_s {
	int32_t value;
	struct list_s* next;
} list_t;
