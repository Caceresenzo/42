all: kfs.iso

boot.o: boot.s
	i386-elf-as boot.s -o boot.o

kernel.o: kernel.cpp
	i386-elf-g++ -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

kfs.bin: boot.o kernel.o
	i386-elf-g++ -T linker.ld -o kfs.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	grub-file --is-x86-multiboot kfs.bin

kfs.iso: kfs.bin grub.cfg
	rm -rf iso/boot/
	mkdir -p iso/boot/grub
	cp kfs.bin iso/boot/
	cp grub.cfg iso/boot/grub/
	grub-mkrescue -o kfs.iso iso/

run-kernel: kfs.bin
	qemu-system-i386 -kernel kfs.bin

run-iso: kfs.iso
	qemu-system-i386 -cdrom kfs.iso

clean:
	rm -f boot.o kernel.o

fclean: clean
	rm -f kfs.bin kfs.iso
