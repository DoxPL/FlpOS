CC = gcc
LINKER = ld
CFLAGS = -m32 -fno-pie -c
OS = $(shell uname)

ifeq ("$(OS)", "Darwin")
CC=x86_64-elf-gcc
LINKER=x86_64-elf-ld
endif
