all: simple advanced

simple:
	make -C simple

advanced:
	make -C advanced

clean:
	make clean -C simple
	make clean -C advanced

list-files:
	@which gcc bc
	@readlink -f ../ft_nm
	@make -s list-files -C simple | xargs -I{} readlink -f simple/{}
	@make -s list-files -C advanced | xargs -I{} readlink -f advanced/{}

.PHONY: simple advanced list-files self
