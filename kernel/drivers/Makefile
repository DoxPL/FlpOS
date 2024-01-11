DRV_OBJS = hw_io.o irq.o

all: $(DRV_OBJS)

hw_io.o:
	@+$(MAKE) -C hw_io

irq.o:
	@+$(MAKE) -C irq

clean:
	@cd hw_io && $(MAKE) clean
	@cd irq && $(MAKE) clean
