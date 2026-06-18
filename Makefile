CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -fno-stack-protector -fno-pie -nostdlib -nostdinc -Wall -Wextra -I.
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

# Todos os .o que precisam compilar
OBJ = boot.o main.o lib/vga_video.o lib/gdt.o lib/idt.o lib/isr.o lib/irq.o lib/timer.o lib/task.o lib/io.o lib/registers.o

all: TampiOS.iso

kernel.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

iso: TampiOS.iso

TampiOS.iso: kernel.elf grub.cfg
	mkdir -p isodir/boot/grub
	cp kernel.elf isodir/boot/
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o TampiOS.iso isodir

run: TampiOS.iso
	qemu-system-i386 -cdrom TampiOS.iso -m 512M -serial stdio

run-kvm: TampiOS.iso
	qemu-system-i386 -enable-kvm -cdrom TampiOS.iso -m 512M -serial stdio

debug: TampiOS.iso
	qemu-system-i386 -cdrom TampiOS.iso -m 512M -s -S -serial stdio

clean:
	rm -f *.o kernel.elf TampiOS.iso
	rm -rf isodir
	rm -f lib/*.o

.PHONY: all iso run run-kvm debug clean
