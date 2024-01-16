OS_BINARY = os_image.img

.PHONY: all

all:
	@+$(MAKE) -C boot
	@+$(MAKE) -C kernel
	@echo "Generating OS image: $(OS_BINARY)"
	@cat boot/boot.bin kernel/kernel.bin > $(OS_BINARY)

clean:
	@rm -f -- os_image.img
	@cd boot && $(MAKE) clean
	@cd kernel && $(MAKE) clean
