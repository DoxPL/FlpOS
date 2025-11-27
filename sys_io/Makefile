include ../common/BuildCommon.mk

HEADERS = ../misc
INCLUDES = $(addprefix -I ,$(HEADERS))

all: sys_io.o

sys_io.o: sys_io.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

clean:
	@rm -f -- sys_io.o
