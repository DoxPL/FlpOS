#include "../../lib/types.h"

#define VIDEO_MEMORY_BASE (uint8_t*)0xB8000
#define VIDEO_MEMORY_INIT_OFFSET 0x140
#define VIDEO_MEMORY VIDEO_MEMORY_BASE + VIDEO_MEMORY_INIT_OFFSET
#define VGA_MATRIX_WIDTH 80
#define VGA_MATRIX_HEIGHT 25
#define VGA_SCR_RESOLUTION VGA_MATRIX_WIDTH * VGA_MATRIX_HEIGHT
#define VGA_MAX_OFFSET (VGA_SCR_RESOLUTION << 1)
#define VGA_BUFF_BOUNDARY (uint8_t*)(0xB8000 + VGA_MAX_OFFSET)

#define SCROLL_BUFF_LINES 10
#define SCROLL_BUFF_SIZE (SCROLL_BUFF_LINES * VGA_MATRIX_HEIGHT) << 1

#define VGA_LOP_OK 0
#define VGA_LOP_BADADDR 1

#define VGA_PORT_CRTC_ADDR 0x3D4
#define VGA_PORT_CRTC_DATA 0x3D5

/* Cursor Disable (byte 5), Cursor Scan Line Start (bytes 4-0) */
#define VGA_REGISTER_CURSOR_START 0x0A
/* Cursor Skew (bytes 6-5), Cursor Scan Line End (bytes 4-0) */
#define VGA_REGISTER_CURSOR_END 0x0B
/* Cursor Location High */
#define VGA_REGISTER_CURSOR_LOC_HIGH 0x0E
/* Cursor Location Low */
#define VGA_REGISTER_CURSOR_LOC_LOW 0x0F

void vga_sync_cursor(void);
void vga_cursor_down(void);
void vga_scroll_up(void);
void vga_scroll_down(void);
void vga_clear_buff(void);
void vga_write_byte(uint8_t*);
void vga_write_word(uint16_t*);
void vga_write_dword(uint32_t*);
void vga_replace_symbol(uint16_t*);
uint8_t vga_add_offset(int16_t);
