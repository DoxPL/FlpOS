#include "../../lib/types.h"

#define VIDEO_MEMORY (char*)0xB8140
#define VGA_MATRIX_WIDTH 80
#define VGA_MATRIX_HEIGHT 25
#define VGA_SCR_RESOLUTION VGA_MATRIX_WIDTH * VGA_MATRIX_HEIGHT
#define VGA_MAX_OFFSET (VGA_SCR_RESOLUTION << 1)
#define VGA_BUFF_BOUNDARY (char*)(0xB8000 + VGA_MAX_OFFSET)

#define SCROLL_BUFF_LINES 10
#define SCROLL_BUFF_SIZE (SCROLL_BUFF_LINES * VGA_MATRIX_HEIGHT) << 1

#define VGA_LOP_OK 0
#define VGA_LOP_BADADDR 1

void cursor_down(void);
void vga_scroll_up(void);
void vga_scroll_down(void);
void vga_clear_buff(void);
void vga_write_byte(int8_t*);
void vga_write_word(int16_t*);
void vga_write_dword(int32_t*);
char vga_set_addr(int8_t*);
char *vga_get_addr(void);
