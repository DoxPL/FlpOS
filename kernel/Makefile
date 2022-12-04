ASM_FLAGS = -f elf -o
ASM = nasm
CC = gcc
CC_FLAGS = -ffreestanding -m32 -g -fno-pie
LINKER = ld
DEL_OBJS = y

kernel.bin: kernel_runner.o kernel.o
	$(LINKER) -o $@ -Ttext 0x1000 kernel_runner.o kernel.o --oformat binary
	@[ "$(DEL_OBJS)" = "y" ] && rm -f -- *.o || exit 0

kernel_runner.o: kernel_runner.asm
	$(ASM) $(ASM_FLAGS) $@ $<

kernel.o: kernel.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	@echo "Cleaning build environment for kernel"
	@rm -f -- *.o *.bin
