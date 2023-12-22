CC = gcc

all: mod_binaries std.o

mod_binaries:
ifeq ("$(OS)", "Darwin")
	$(eval CC=x86_64-elf-gcc)
endif

std.o: std.h std.c
	$(CC) -c std.c

clean:
	@rm -f -- *.o
