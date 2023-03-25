FROM ubuntu:latest

ENV PREFIX="/opt/cross"
ENV TARGET=i386-elf
ENV PATH="$PREFIX/bin:$PATH"

RUN apt update && \
	apt install -y zsh wget curl screen make git tar xz-utils build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev grub2 xorriso qemu-system nasm && \
	sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

WORKDIR /opt

RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.40.tar.xz && \
	tar xvf binutils-2.40.tar.xz && \
	cd binutils-2.40 && \
	mkdir build && \
	cd build && \
	../configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && \
	make -j$(nproc) && \
	make install && \
	cd ../../ && \
	rm -rf binutils-2.40

RUN wget https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.xz && \
	tar xvf gcc-12.2.0.tar.xz && \
	cd gcc-12.2.0 && \
	mkdir build && \
	cd build && \
	../configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers && \
	make all-gcc -j$(nproc) && \
	make all-target-libgcc -j$(nproc) && \
	make install-gcc && \
	make install-target-libgcc && \
	cd ../../ && \
	rm -rf gcc-12.2.0

WORKDIR /workspace
ENTRYPOINT zsh
