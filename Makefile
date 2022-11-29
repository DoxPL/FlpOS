LINKER = ld

.PHONY: all

all:
	@+$(MAKE) -C boot
	@+$(MAKE) -C kernel
	# Concatenate bootloader and kernel
	@cat boot/boot.bin kernel/kernel.bin > os_image.img

clean:
	@rm -f -- os_image.img
	@cd boot && $(MAKE) clean
	@cd kernel && $(MAKE) clean
