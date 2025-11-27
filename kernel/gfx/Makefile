include ../../common/BuildCommon.mk

HEADERS = ../../misc ../../lib ../drivers/hw_io
INCLUDES = $(addprefix -I ,$(HEADERS))

all: vga_generic.o

vga_generic.o: vga_generic.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

clean:
	@rm -f -- vga_generic.o
