CC = gcc
CFLAGS = -m32 -fno-pie -c
OS = $(shell uname)

all: mod_binaries vga_generic.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
endif

vga_generic.o: vga_generic.c
	$(CC) $(CFLAGS) $<

clean:
	@rm -f -- vga_generic.o
