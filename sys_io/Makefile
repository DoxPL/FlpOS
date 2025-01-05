CC = gcc
CFLAGS = -m32 -fno-pie -c
HEADERS = ../misc
INCLUDES = $(addprefix -I ,$(HEADERS))
OS = $(shell uname)

all: mod_binaries sys_io.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
endif

sys_io.o: sys_io.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

clean:
	@rm -f -- sys_io.o
