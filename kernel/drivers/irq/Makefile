CC = gcc
CFLAGS = -m32 -fno-pie -c
LINKER = ld
HEADERS = ../hw_io ../../gfx ../../../misc
INCLUDES = $(addprefix -I ,$(HEADERS))
OS = $(shell uname)

all: mod_binaries idt.o kbrd_queue.o irq_handler.o pic_8259.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
LINKER=x86_64-elf-ld
endif

idt.o: idt.c
	$(CC) $(INCLUDES) -mgeneral-regs-only $(CFLAGS) $< -o $@

kbrd_queue.o: kbrd_queue.c
	$(CC) $(INCLUDES) -mgeneral-regs-only $(CFLAGS) $< -o kbrd_queue.o

irq_handler.o: irq_handler.c kbrd_queue.o
	$(CC) $(INCLUDES) -mgeneral-regs-only $(CFLAGS) $< -o irq.o
	$(LINKER) -m elf_i386 -r irq.o idt.o kbrd_queue.o -o $@

pic_8259.o: pic_8259.c
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	@rm -f -- *.o
