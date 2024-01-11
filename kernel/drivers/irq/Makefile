CC = gcc
CFLAGS = -m32 -fno-pie -mgeneral-regs-only -c
LINKER = ld
HEADERS = ../hw_io ../../../lib
INCLUDES = $(addprefix -I ,$(HEADERS))
OS = $(shell uname)

all: mod_binaries idt.o irq_handler.o pic_8259.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
LINKER=x86_64-elf-ld
endif

idt.o: idt.c
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

irq_handler.o: irq_handler.c
	$(CC) $(INCLUDES) $(CFLAGS) $< -o irq.o
	$(LINKER) -m elf_i386 -r irq.o idt.o -o $@

pic_8259.o: pic_8259.c
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

irq.o: idt.o irq_handler.o
	$(LINKER) -m elf_i386 -r $< -o $@

clean:
	@rm -f -- *.o
