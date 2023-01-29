ASM_SOURCE = $(shell find -type f -name \*.s)
CPP_SOURCE = $(shell find -type f -name \*.cpp)
OBJECTS = $(ASM_SOURCE:.s=.o) $(CPP_SOURCE:.cpp=.o)

TARGET_BIN = kfs.bin
TARGET_ISO = kfs.iso

AS = i386-elf-as
CC = i386-elf-g++
CCFLAGS = -O0 -g3 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs -Wfatal-errors

all: kfs.bin

.s.o:
	$(AS) $< -o $@

.cpp.o:
	$(CC) -c $< -o $@ -Iinclude $(CCFLAGS)

kfs.bin: $(OBJECTS) boot/linker.ld
	$(CC) -T boot/linker.ld -o $(TARGET_BIN) $(OBJECTS) $(CCFLAGS)
	grub-file --is-x86-multiboot $(TARGET_BIN)

kfs.iso: $(TARGET_BIN) boot/grub.cfg
	rm -rf /tmp/iso/boot/
	mkdir -p /tmp/iso/boot/grub
	cp $(TARGET_BIN) /tmp/iso/boot/
	cp boot/grub.cfg /tmp/iso/boot/grub/
	grub-mkrescue -o $(TARGET_ISO) /tmp/iso/

run-kernel: $(TARGET_BIN)
	qemu-system-i386 -kernel $(TARGET_BIN)

run-iso: $(TARGET_ISO)
	qemu-system-i386 -cdrom $(TARGET_ISO)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -f $(TARGET_BIN) $(TARGET_ISO)
