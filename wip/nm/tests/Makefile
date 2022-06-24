DOCKER_IMAGE = nm-test-compiler

all: simple advanced

docker:
	docker build -t $(DOCKER_IMAGE) .

simple: docker
	docker run --rm -it -v $(shell pwd):/app $(DOCKER_IMAGE) make -C simple

advanced: docker
	docker run --rm -it -v $(shell pwd):/app $(DOCKER_IMAGE) make -C advanced

clean:
	make clean -C simple
	make clean -C advanced

list-files:
	@which gcc bc
	@readlink -f ../ft_nm
	@make -s list-files -C simple | xargs -I{} readlink -f simple/{}
	@make -s list-files -C advanced | xargs -I{} readlink -f advanced/{}

.PHONY: simple advanced list-files
