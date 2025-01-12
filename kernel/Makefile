ASM_FLAGS = -f elf -o
ASM = nasm
CC = gcc
CC_FLAGS = -ffreestanding -m32 -g -fno-pie -I ..
OS = $(shell uname)
LINKER = ld
HEADERS = ../misc ../user drivers drivers/irq drivers/io
INCLUDES = $(addprefix -I ,$(HEADERS))
OBJS = kernel_runner.o ../lib/std.o ../lib/memory.o ../user/cli.o gfx/vga_generic.o drivers/irq/pic_8259.o drivers/irq/irq_handler.o kernel.o
DEL_OBJS = n
export OBJS

.PHONY: drivers
all: mod_binaries drivers $(OBJS) kernel.bin

mod_binaries:
ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
LINKER=x86_64-elf-ld
endif

kernel.bin: $(OBJS)
	$(LINKER) -o $@ -Ttext 0x1000 --entry main $(OBJS) --oformat binary -m elf_i386
	@[ "$(DEL_OBJS)" = "y" ] && rm -f -- *.o || exit 0

drivers:
	@+$(MAKE) -C drivers

gfx/vga_generic.o:
	@+$(MAKE) -C gfx

kernel_runner.o: kernel_runner.asm
	$(ASM) $(ASM_FLAGS) $@ $<

../lib/std.o:
	@+$(MAKE) -C ../lib

kernel.o: kernel.c
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning build environment for kernel"
	@rm -f -- *.o *.bin
	@cd ../lib && $(MAKE) clean
	@cd gfx && $(MAKE) clean
	@cd drivers && $(MAKE) clean
