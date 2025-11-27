include ../common/AsmCommon.mk

ASM_FLAGS = -f bin -o

boot.bin: boot.asm
	@echo "Building bootloader..."
	$(ASM) $(ASM_FLAGS) $@ $<

clean:
	@echo "Cleaning build environment"
	@rm -f -- *.o *.img *.bin
