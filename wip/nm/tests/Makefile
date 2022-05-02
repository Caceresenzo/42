all: simple advanced

simple:
	make -C simple

advanced:
	make -C advanced

clean:
	make clean -C simple
	make clean -C advanced

list-files:
	make list-files -C simple | xargs -I{} echo simple/{}
	make list-files -C advanced | xargs -I{} echo advanced/{}

.PHONY: simple advanced
