# BeeOS Makefile
CC = gcc
NASM = nasm
CFLAGS = -m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra
LDFLAGS = -m elf_i386 -nostdlib

# Source files
SRCS = src/boot.asm src/kernel.c src/shell.c
OBJS = $(SRCS:.asm=.o)
OBJS := $(OBJS:.c=.o)

# Output
TARGET = beeOS.iso
KERNEL = beeOS.bin

.PHONY: all clean iso run

all: $(TARGET)

# Compile assembly files
%.o: %.asm
	$(NASM) -f elf32 $< -o $@

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link kernel
$(KERNEL): $(OBJS)
	ld $(LDFLAGS) -T linker.ld -o $@ $^

# Create ISO
iso: $(KERNEL)
	mkdir -p iso/boot/grub
	cp $(KERNEL) iso/boot/
	cp iso/boot/grub/grub.cfg iso/boot/grub/
	grub-mkrescue -o $(TARGET) iso

# Clean build artifacts
clean:
	rm -rf *.o src/*.o $(KERNEL) $(TARGET) iso/boot/$(KERNEL)

# Run in QEMU
run: $(TARGET)
	qemu-system-i386 -cdrom $(TARGET)
