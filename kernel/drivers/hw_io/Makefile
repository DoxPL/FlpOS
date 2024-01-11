CC = gcc
CC_FLAGS = -ffreestanding -m32 -g -fno-pie -I ..
OS = $(shell uname)

all: mod_binaries hw_io.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
endif

hw_io.o: hw_io.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	@rm -f -- *.o
