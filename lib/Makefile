include ../common/BuildCommon.mk

HEADERS = ../misc ../kernel/gfx/ ../sys_io
INCLUDES = $(addprefix -I ,$(HEADERS))
OBJS = memory.o std.o

all: $(OBJS)

../sys_io/sys_io.o:
	@+$(MAKE) -C ../sys_io

memory.o: memory.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

std.o: std.c ../sys_io/sys_io.o
	$(CC) $(CFLAGS) $(INCLUDES) std.c -o stdlib.o
	$(LINKER) -m elf_i386 -r ../sys_io/sys_io.o stdlib.o -o $@

clean:
	@rm -f -- *.o
