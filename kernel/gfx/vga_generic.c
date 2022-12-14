#include "vga_generic.h"

static char *vga_current_addr = VIDEO_MEMORY;
static char scroll_buff[SCROLL_BUFF_SIZE];

static void vga_adjust_addr(unsigned short shift) {
	vga_current_addr += shift;
}

void vga_scroll_up(void) {
	char *cell;
	const unsigned short line_bytes = VGA_MATRIX_WIDTH << 1;

	/* Read buffer */
	for (cell = VIDEO_MEMORY; cell < VIDEO_MEMORY + line_bytes; cell++) {
		*cell = 0x0;
	}

	for (cell = VGA_BUFF_MAX - 1; cell >= VIDEO_MEMORY + line_bytes; cell--) {
		*cell = *(cell - line_bytes);
	}
}

void vga_scroll_down(void) {
	char *cell;
	const unsigned short line_bytes = VGA_MATRIX_WIDTH << 1;
	for (cell = VIDEO_MEMORY; cell < VGA_BUFF_MAX - line_bytes; cell++) {
		*cell = *(cell + line_bytes);
	}
	vga_current_addr -= line_bytes;
}

void vga_clear_buff(void) {
	unsigned int cell;
	for (cell = 0; cell < VGA_MAX_OFFSET; cell++) {
		*(VIDEO_MEMORY - 0x140 + cell) = 0x0;
	}
	vga_current_addr = VIDEO_MEMORY - 0x140;
}

void vga_write_byte(char *data) {
	*vga_current_addr++ = *data;
}

void vga_write_word(short *data) {
	*((short *)vga_current_addr) = *data;
	vga_current_addr += sizeof(*data);
}

void vga_write_dword(int *data) {
	*((int *)vga_current_addr) = *data;
	vga_current_addr += sizeof(*data);
}

char vga_set_addr(char *new_addr) {
	if (new_addr < VIDEO_MEMORY || new_addr > VGA_BUFF_MAX) {
		return VGA_LOP_BADADDR;
	}
	vga_current_addr = new_addr;
	return VGA_LOP_OK;
}

char *vga_get_addr(void) {
	return vga_current_addr;
}
