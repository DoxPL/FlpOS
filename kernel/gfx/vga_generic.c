#include "vga_generic.h"
#include "std.h"

static uint8_t *vga_current_addr = VIDEO_MEMORY;
static int8_t scroll_buff[SCROLL_BUFF_SIZE];

void cursor_down(void) {
    uint8_t bytes_in_row = 0U;
    bytes_in_row = (vga_get_addr() - VIDEO_MEMORY) % (VGA_MATRIX_WIDTH << 1);
    vga_set_addr(vga_get_addr() + ((VGA_MATRIX_WIDTH << 1) - bytes_in_row));
}

void vga_adjust_addr(uint16_t shift) {
    vga_current_addr += shift;
    if (vga_current_addr >= VGA_BUFF_BOUNDARY) {
        vga_scroll_down();
        vga_current_addr -= (VGA_MATRIX_WIDTH << 1);
        /* Fill the last line with spaces */
        mset16(vga_current_addr, 0x20, VGA_MATRIX_WIDTH << 1);
    }
}

void vga_scroll_up(void) {
    int8_t *cell;
    const uint16_t line_bytes = VGA_MATRIX_WIDTH << 1;

    /* Read buffer */
    for (cell = VIDEO_MEMORY; cell < VIDEO_MEMORY + line_bytes; cell++) {
        *cell = 0x0;
    }

    for (cell = VGA_BUFF_BOUNDARY - 1; cell >= VIDEO_MEMORY + line_bytes; cell--) {
        *cell = *(cell - line_bytes);
    }
}

void vga_scroll_down(void) {
    int8_t *cell;
    const uint16_t line_bytes = VGA_MATRIX_WIDTH << 1;
    for (cell = VIDEO_MEMORY; cell < VGA_BUFF_BOUNDARY - line_bytes; cell++) {
        *cell = *(cell + line_bytes);
    }
}

void vga_clear_buff(void) {
    uint32_t cell;
    for (cell = 0; cell < VGA_MAX_OFFSET; cell++) {
        *(VIDEO_MEMORY - 0x140 + cell) = 0x0;
    }
    vga_current_addr = VIDEO_MEMORY - 0x140;
}

void vga_write_byte(int8_t *data) {
    *vga_current_addr = *data;
    vga_adjust_addr(sizeof(*data));
}

void vga_write_word(int16_t *data) {
    *((int16_t *)vga_current_addr) = *data;
    vga_adjust_addr(sizeof(*data));
}

void vga_write_dword(int32_t *data) {
    *((int32_t *)vga_current_addr) = *data;
    vga_adjust_addr(sizeof(*data));
}

int8_t vga_set_addr(int8_t *new_addr) {
    if (new_addr < VIDEO_MEMORY || new_addr > VGA_BUFF_BOUNDARY) {
        return VGA_LOP_BADADDR;
    }
    vga_current_addr = new_addr;
    return VGA_LOP_OK;
}

int8_t *vga_get_addr(void) {
    return vga_current_addr;
}
