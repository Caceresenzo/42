all: binaries

binaries:
	unzip binaries.zip -d binaries/

clean:
	rm -rf binaries

list-files:
	@find binaries/ -type f

.PHONY: all clean list-files
