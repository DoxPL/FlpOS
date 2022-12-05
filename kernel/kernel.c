/* OS kernel code */
#include "lib/types.h"
#include "gfx/vga_generic.h"

#define kprint(str) kprint_c(str, 0x0F)

void kprint_c(const u8ptr_t text, color_t color) {
	u8ptr_t char_ptr = text;
	uint16_t char_data = 0;
	uint8_t bytes_in_row = 0;
	while(*char_ptr != '\0') {
		if (*char_ptr == '\n') {
			bytes_in_row = (vga_get_addr() - VIDEO_MEMORY) % (VGA_MATRIX_WIDTH << 1);
			vga_set_addr(vga_get_addr() + ((VGA_MATRIX_WIDTH << 1) - bytes_in_row));
			char_ptr++;
			continue;
		} else if (*char_ptr == '\t') {
			vga_set_addr(vga_get_addr() + 0x8);
			char_ptr++;
			continue;
		}
		char_data = (color << 8) | *char_ptr++;
		vga_write_word(&char_data);
	}
}

void tty_ctest(void) {
	uint8_t buff[VGA_MATRIX_WIDTH + 1];
	buff[VGA_MATRIX_WIDTH] = '\0';
	uint16_t cnum, color;
	for (cnum = 0; cnum < VGA_MATRIX_WIDTH; cnum++) {
		buff[cnum] = '#'; //0xDB;
	}
	for (color = 1; color < 16; color++) {
		kprint_c(buff, color);
	}
}

void main(void) {
	tty_ctest();
	kprint("Kernel ready!");
	vga_clear_buff();
	kprint("New line");
	return;
}
