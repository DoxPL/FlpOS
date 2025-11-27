include ../../../common/BuildCommon.mk

HEADERS = ../hw_io ../../gfx ../../../misc ../../../lib
INCLUDES = $(addprefix -I ,$(HEADERS))

all: idt.o kbrd_queue.o irq_handler.o pic_8259.o

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
