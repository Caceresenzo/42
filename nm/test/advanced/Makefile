PROJECTS = bash bc bzip2 file less grep binutils make nano

all: $(PROJECTS)

clean:
	rm -rf $(PROJECTS)

bash:
	sh download-and-compile.sh bash https://ftp.gnu.org/gnu/bash/bash-5.1.16.tar.gz
	sh copy-elf.sh bash

bc:
	sh download-and-compile.sh bc https://github.com/gavinhoward/bc/releases/download/5.2.4/bc-5.2.4.tar.xz
	sh copy-elf.sh bc

bzip2:
	sh download-and-compile.sh bzip2 https://www.sourceware.org/pub/bzip2/bzip2-1.0.8.tar.gz
	sh copy-elf.sh bzip2

file:
	sh download-and-compile.sh file https://astron.com/pub/file/file-5.41.tar.gz
	sh copy-elf.sh file

less:
	sh download-and-compile.sh less https://www.greenwoodsoftware.com/less/less-590.tar.gz
	sh copy-elf.sh less

grep:
	sh download-and-compile.sh grep https://ftp.gnu.org/gnu/grep/grep-3.7.tar.xz
	sh copy-elf.sh grep

binutils:
	sh download-and-compile.sh binutils https://mirror.cyberbits.eu/gnu/binutils/binutils-2.38.tar.xz
	sh copy-elf.sh binutils

make:
	sh download-and-compile.sh make https://ftp.gnu.org/gnu/make/make-4.3.tar.gz
	sh copy-elf.sh make

nano:
	sh download-and-compile.sh nano https://www.nano-editor.org/dist/v6/nano-6.3.tar.xz
	sh copy-elf.sh nano

list-files:
	@find $(PROJECTS) -type f

.PHONY: all clean list-files
