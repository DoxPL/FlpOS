CC = gcc
LINKER = ld
HEADERS = ../misc ../kernel/gfx/ ../sys_io
INCLUDES = $(addprefix -I ,$(HEADERS))
CFLAGS = -m32 -fno-pie -c
OBJS = memory.o std.o
OS = $(shell uname)

all: mod_binaries $(OBJS)

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
LINKER=x86_64-elf-ld
endif

../sys_io/sys_io.o:
	@+$(MAKE) -C ../sys_io

memory.o: memory.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

std.o: std.c ../sys_io/sys_io.o
	$(CC) $(CFLAGS) $(INCLUDES) std.c -o stdlib.o
	$(LINKER) -m elf_i386 -r ../sys_io/sys_io.o stdlib.o -o $@

clean:
	@rm -f -- *.o
