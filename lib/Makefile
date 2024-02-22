CC = gcc
HEADERS = ../kernel/gfx/
INCLUDES = $(addprefix -I ,$(HEADERS))
CFLAGS = -m32 -fno-pie -c
OS = $(shell uname)

all: mod_binaries std.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
endif

std.o: std.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

clean:
	@rm -f -- *.o
