#pragma once

#define NULL (void*)0
#define true 1
#define false 0

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned char bool_t;
typedef long long int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;
typedef unsigned int* u32ptr_t;
typedef unsigned short* u16ptr_t;
typedef unsigned char* u8ptr_t;
typedef void* vptr_t;
typedef char* string;
typedef unsigned int uword_t;
typedef unsigned int size_t;

typedef struct list_s {
    int32_t value;
    struct list_s* next;
} list_t;

typedef enum Color {
    VGA_CBLACK = 0,
    VGA_CBLUE,
    VGA_CGREEN,
    VGA_CCYAN,
    VGA_CRED,
    VGA_CPURPLE,
    VGA_CBROWN,
    VGA_CGRAY,
    VGA_CDGRAY,
    VGA_CLBLUE,
    VGA_CLGREEN,
    VGA_CLCYAN,
    VGA_CLRED,
    VGA_CLPURPLE,
    VGA_CYELLOW,
    VGA_CWHITE
} color_t;
