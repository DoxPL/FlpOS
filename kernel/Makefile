ASM_FLAGS = -f elf -o
ASM = nasm
CC = gcc
CC_FLAGS = -ffreestanding -m32 -g -fno-pie -I ..
LINKER = ld
OBJS = kernel_runner.o kernel.o gfx/vga_generic.o
DEL_OBJS = y

kernel.bin: $(OBJS)
	$(LINKER) -o $@ -Ttext 0x1000 $(OBJS) --oformat binary
	@[ "$(DEL_OBJS)" = "y" ] && rm -f -- *.o || exit 0

gfx/vga_generic.o:
	@+$(MAKE) -C gfx

kernel_runner.o: kernel_runner.asm
	$(ASM) $(ASM_FLAGS) $@ $<

kernel.o: kernel.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	@echo "Cleaning build environment for kernel"
	@rm -f -- *.o *.bin
	@cd gfx && $(MAKE) clean
