CC = gcc
CFLAGS = -m32 -fno-pie -c
OS = $(shell uname)

all: mod_binaries std.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
	$(eval CC=x86_64-elf-gcc)
endif

std.o: std.h std.c
	$(CC) $(CFLAGS) std.c

clean:
	@rm -f -- *.o
