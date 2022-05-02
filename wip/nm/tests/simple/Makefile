all: binaries

binaries:
	sh compile.sh

clean:
	rm -rf binaries

list-files: binaries
	@find binaries/ -type f

.PHONY: all clean list-files
