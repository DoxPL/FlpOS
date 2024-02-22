CC = gcc
CFLAGS = -m32 -fno-pie -c
HEADERS = ../../lib/
INCLUDES = $(addprefix -I ,$(HEADERS))
OS = $(shell uname)

all: mod_binaries vga_generic.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
endif

vga_generic.o: vga_generic.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

clean:
	@rm -f -- vga_generic.o
