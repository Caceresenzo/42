ifneq (,$(findstring Microsoft,$(shell uname -r)))
	CURRENT_WORKING_DIRECTORY = "%cd%"
else
    CURRENT_WORKING_DIRECTORY = $(shell pwd)
endif

DOCKER_IMAGE = nm-test-compiler

all: simple advanced mac-o

docker:
	docker build -t $(DOCKER_IMAGE) .

simple: docker
	docker run --rm -it -v $(CURRENT_WORKING_DIRECTORY):/app $(DOCKER_IMAGE) make -C simple

advanced: docker
	docker run --rm -it -v $(CURRENT_WORKING_DIRECTORY):/app $(DOCKER_IMAGE) make -C advanced

mac-o:
	make -C mac-o

clean:
	make clean -C simple
	make clean -C advanced
	make clean -C mac-o

list-files:
	@which gcc bc
	@readlink -f ../ft_nm
	@make -s list-files -C simple | xargs -I{} readlink -f simple/{}
	@make -s list-files -C mac-o | xargs -I{} readlink -f mac-o/{}
	@make -s list-files -C advanced | xargs -I{} readlink -f advanced/{}

.PHONY: simple advanced mac-o list-files
