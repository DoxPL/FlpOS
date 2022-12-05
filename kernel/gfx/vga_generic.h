#define VIDEO_MEMORY (char*)0xB8140
#define VGA_MATRIX_WIDTH 80
#define VGA_MATRIX_HEIGHT 25
#define VGA_SCR_RESOLUTION VGA_MATRIX_WIDTH * VGA_MATRIX_HEIGHT
#define VGA_MAX_OFFSET VGA_SCR_RESOLUTION << 1
#define VGA_BUFF_MAX 0xB8000 + VGA_MAX_OFFSET

#define VGA_LOP_OK 0
#define VGA_LOP_BADADDR 1

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

typedef unsigned int vsize_t;

void vga_clear_buff(void);
void vga_write_byte(char*);
void vga_write_word(short*);
void vga_write_dword(int*);
char vga_set_addr(char*);
char *vga_get_addr(void);
