CC = gcc
LINKER = ld
HEADERS = ../misc ../lib
INCLUDES = $(addprefix -I ,$(HEADERS))
CFLAGS = -m32 -fno-pie -c
OBJS = cli.o
OS = $(shell uname)

all: mod_binaries $(OBJS)

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
LINKER=x86_64-elf-ld
endif

cli.o: cli.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

clean:
	@rm -f -- *.o
