#include "vga_generic.h"
#include "memory.h"
#include "hw_io.h"
#include "std.h"

static uint8_t *vga_current_addr = VIDEO_MEMORY;
static uint8_t scroll_buff[SCROLL_BUFF_SIZE];

static void vga_update_cursor(int8_t pos_x, int8_t pos_y) {
    int16_t current_pos = pos_y * VGA_MATRIX_WIDTH + pos_x;
    outb(VGA_PORT_CRTC_ADDR, VGA_REGISTER_CURSOR_LOC_LOW);
    outb(VGA_PORT_CRTC_DATA, current_pos & 0xFF);
    outb(VGA_PORT_CRTC_ADDR, VGA_REGISTER_CURSOR_LOC_HIGH);
    outb(VGA_PORT_CRTC_DATA, (current_pos >> 8) & 0xFF);
}

static void vga_append_line(void) {
    if (vga_current_addr >= (uint8_t*)VGA_BUFF_BOUNDARY) {
        vga_scroll_down();
        vga_current_addr -= (VGA_MATRIX_WIDTH << 1);
        /* Fill the last line with spaces */
        mset16(vga_current_addr, 0x20, VGA_MATRIX_WIDTH << 1);
    }
}

void vga_sync_cursor(void) {
    uint8_t col, row;
    uint16_t delta = vga_current_addr - VIDEO_MEMORY;
    col = (delta / 2) % VGA_MATRIX_WIDTH;
    row = (delta / 2) / VGA_MATRIX_WIDTH;
    vga_update_cursor(col, row);
}

void vga_cursor_down(void) {
    uint8_t bytes_in_row = 0U;
    bytes_in_row = (vga_current_addr - VIDEO_MEMORY) % (VGA_MATRIX_WIDTH << 1);
    vga_add_offset((VGA_MATRIX_WIDTH << 1) - bytes_in_row);
}

void vga_scroll_up(void) {
    uint8_t *cell;
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
    uint8_t *cell;
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

void vga_write_byte(uint8_t data) {
    *vga_current_addr = data;
    vga_add_offset(sizeof(data));
    vga_sync_cursor();
}

void vga_write_word(uint16_t data) {
    *((uint16_t *)vga_current_addr) = data;
    vga_add_offset(sizeof(data));
    vga_sync_cursor();
}

void vga_write_dword(uint32_t data) {
    *((uint32_t *)vga_current_addr) = data;
    vga_add_offset(sizeof(data));
    vga_sync_cursor();
}

void vga_replace_symbol(uint16_t new_data) {
    *((uint32_t *)vga_current_addr) = new_data;
}

uint8_t vga_add_offset(int16_t offset) {
    uint8_t *new_addr = vga_current_addr + offset;

    if (new_addr < VIDEO_MEMORY || new_addr > VGA_BUFF_BOUNDARY) {
        return VGA_LOP_BADADDR;
    }

    vga_current_addr = new_addr;
    vga_append_line();
    vga_sync_cursor();
    return VGA_LOP_OK;
}

void vga_write_user_data(uint16_t data, size_t size) {
    uint16_t char_data;
    switch (data)
    {
        case '\n':
            vga_cursor_down();
            break;
        case '\t':
            vga_add_offset(0x8);
            break;
        case '\b':
            vga_add_offset(-0x2);
            char_data = (VGA_CWHITE << 8) | 0x20;
            vga_replace_symbol(char_data);
            break;
        default:
            vga_write_word(data);
            break;
    }
}
