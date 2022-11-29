ASM = nasm
LINKER = ld
FLAGS_BOOT = -f bin -o
FLAGS_RUN = -f elf -o

boot.bin: boot.asm
	@echo "Building bootloader..."
	$(ASM) $(FLAGS_BOOT) $@ $<

clean:
	@echo "Cleaning build environment"
	@rm -f -- *.o *.img *.bin
