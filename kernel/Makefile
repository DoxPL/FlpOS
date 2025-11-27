include ../common/AsmCommon.mk
include ../common/BuildCommon.mk

ASM_FLAGS = -f elf -o
ASM = nasm

CFLAGS += -g -ffreestanding -I ..

HEADERS = ../misc drivers drivers/irq drivers/io
INCLUDES = $(addprefix -I ,$(HEADERS))
OBJS = kernel_runner.o ../lib/std.o ../lib/memory.o gfx/vga_generic.o drivers/irq/pic_8259.o drivers/irq/irq_handler.o kernel.o
DEL_OBJS = n
export OBJS

.PHONY: drivers
all: drivers $(OBJS) kernel.bin

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
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	@echo "Cleaning build environment for kernel"
	@rm -f -- *.o *.bin
	@$(MAKE) -C ../lib clean
	@$(MAKE) -C gfx clean
	@$(MAKE) -C drivers clean
