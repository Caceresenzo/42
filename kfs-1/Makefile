S_SOURCE = $(shell find -type f -name \*.S)
NASM_SOURCE = $(shell find -type f -name \*.s)
C_SOURCE = $(shell find -type f -name \*.c)
CPP_SOURCE = $(shell find -type f -name \*.cpp)
OBJECTS = $(S_SOURCE:.S=.o) $(NASM_SOURCE:.s=.o) $(C_SOURCE:.c=.o) $(CPP_SOURCE:.cpp=.o)

TARGET_BIN = kfs.bin
TARGET_ISO = kfs.iso

AC = i386-elf-as
AFLAGS = 
NASMC = nasm
NASMFLAGS = -f elf
CC = i386-elf-gcc
CPPC = i386-elf-g++
CFLAGS = -O0 -g3 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -Wfatal-errors
CPPFLAGS = $(CFLAGS) -fno-rtti
LINKERFLAGS = $(CPPFLAGS) -lgcc

all: $(TARGET_ISO)

.S.o:
	$(AC) $< -o $@ $(AFLAGS)

.s.o:
	$(NASMC) $< -o $@ $(NASMFLAGS)

.c.o:
	$(CC) -c $< -o $@ -Iinclude $(CFLAGS)

.cpp.o:
	$(CPPC) -c $< -o $@ -Iinclude $(CPPFLAGS)

$(TARGET_BIN): $(OBJECTS) boot/linker.ld
	$(CC) -T boot/linker.ld -o $(TARGET_BIN) $(OBJECTS) $(LINKERFLAGS)
	grub-file --is-x86-multiboot $(TARGET_BIN)

$(TARGET_ISO): $(TARGET_BIN) boot/grub.cfg
	rm -rf /tmp/iso/boot/
	mkdir -p /tmp/iso/boot/grub
	cp $(TARGET_BIN) /tmp/iso/boot/
	cp boot/grub.cfg /tmp/iso/boot/grub/
	grub-mkrescue -o $(TARGET_ISO) /tmp/iso/

run: $(TARGET_ISO)
	qemu-system-i386 -cdrom $(TARGET_ISO) # -d int

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -f $(TARGET_BIN) $(TARGET_ISO)

re: fclean all

workspace-image:
	mkdir -p empty
	docker build -t kfs-builder -f Dockerfile empty
	rm -rf empty

workspace-run:
	if grep -qi microsoft /proc/version; then \
		echo "docker: running from wsl linux"; \
		docker run -it --rm -v %cd%:/workspace -e DISPLAY=host.docker.internal:0.0 kfs-builder; \
	else \
		echo "docker: running from native linux"; \
		docker run -it --rm -v $$(pwd):/workspace -v /tmp/.X11-unix/:/tmp/.X11-unix/ -e DISPLAY=$$DISPLAY kfs-builder; \
	fi \
