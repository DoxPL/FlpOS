CC = gcc
CFLAGS = -fno-pie -c

vga_generic.o: vga_generic.c vga_generic.h
	$(CC) $(CFLAGS) $<

clean:
	@rm -f -- vga_generic.o
