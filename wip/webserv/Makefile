# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 15:11:33 by ecaceres          #+#    #+#              #
#    Updated: 2020/11/30 16:18:47 by alicetetu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

USE_FSANITIZE			= false
RUN_TESTS				= 0
DO_MAKE_RE				= 0
RUN_WITH_VALGRIND		= 0
SIEGE_URL				= host.docker.internal
SIEGE_FILE				= /wordpress/
ARGS					=
VALGRIND_ARGS			=

SOURCE_DIR				= source
PROJECT_MAKE			= make -s -C $(SOURCE_DIR) USE_FSANITIZE=$(USE_FSANITIZE) RUN_TESTS=$(RUN_TESTS)

ifeq ($(shell if grep -q Microsoft /proc/version 2>/dev/null; then echo "wsl"; else echo "linux"; fi),wsl)
    DOCKER := /mnt/c/Windows/System32/cmd.exe /c docker
else
    DOCKER := docker
endif

all: --touch-test-files
	@$(PROJECT_MAKE) all
    
fclean:
	@$(PROJECT_MAKE) fclean
    
clean:
	@$(PROJECT_MAKE) clean
    
re:
	@$(PROJECT_MAKE) re
    
rej:
	@$(PROJECT_MAKE) fclean
	@$(PROJECT_MAKE) all -j $(shell nproc)

norm:
	@$(PROJECT_MAKE) norm

update:
	@$(PROJECT_MAKE) update

run: RUN_TESTS=0
run: all
	@$(PROJECT_MAKE) ARGS="$(ARGS)" run

run-here: RUN_TESTS=0
run-here: ARGS=-f source/conf4.json
run-here: all
	@./$(SOURCE_DIR)/webserv $(ARGS)

run-with-valgrind: RUN_TESTS=0
run-with-valgrind: all
	@$(PROJECT_MAKE) ARGS="$(ARGS)" VALGRIND_ARGS="$(VALGRIND_ARGS)" run-with-valgrind

test: RUN_TESTS=1
test: all
	@$(PROJECT_MAKE) ARGS="$(ARGS)" run

test-configs: RUN_TESTS=0
test-configs: all
	@ \
	previous=""; \
	for f in $(SOURCE_DIR)/tests/configs/invalid-*.json; do \
		name=$$(basename $$f .json | sed -e "s/^invalid-//"); \
		key=$$(echo $$name | awk -F --- '{ print $$1 }'); \
		error=$$(echo $$name | awk -F --- '{ print $$2 }'); \
		\
		if ! test -z "$$TERM"; then \
			if test "$$previous" = "$$key"; then \
				key=""; \
			else \
				printf "%$$(tput cols)s" | tr " " "-"; \
				previous=$$key; \
			fi; \
			printf "%s \033[30G %s \033[60G" "$$key" "$$error"; \
		else \
			printf "%s %s -- " "$$key" "$$error"; \
		fi; \
		\
		! ./$(SOURCE_DIR)/webserv -c -f $$f; \
	done

docker-build-siege:
	@$(DOCKER) build -t siege -f docker/siege/Dockerfile .

docker-build-base:
	@$(DOCKER) build -t webserv-base -f docker/Dockerfile.base .

docker-build-run: all docker-build-base
	@$(DOCKER) build -t webserv-run -f docker/Dockerfile.run .

docker-build-test: all docker-build-base
	@$(DOCKER) build --build-arg DO_MAKE_RE=$(DO_MAKE_RE) -t webserv-test -f docker/Dockerfile.test .

docker-run: docker-build-run
	@$(DOCKER) run --rm -it -p 80:80 webserv-run $(ARGS)

docker-test: docker-build-test
	@$(DOCKER) run --rm -it -p 80:80 -e RUN_WITH_VALGRIND=$(RUN_WITH_VALGRIND) webserv-test $(ARGS)

siege: docker-build-siege
	@$(DOCKER) run --rm -it -t siege -d1 -c50 -b -i $(SIEGE_URL)$(SIEGE_FILE)

--touch-test-files:
	@#echo ${RUN_TESTS} $$(bash -c "test -f '.test'; echo $$?") # DEBUG
	@bash -c "if [[ ('${RUN_TESTS}' = 0 && -f '.test') || ('${RUN_TESTS}' != 0 && ! -f '.test') ]]; then touch source/main.cpp source/tests/units/*.cpp; fi"
	@bash -c "if [[ '${RUN_TESTS}' = 0 && -f '.test' ]]; then rm .test; fi"
	@bash -c "if [[ '${RUN_TESTS}' != 0 && ! -f '.test' ]]; then touch .test; fi"

.PHONY: all clean fclean re norm update run test docker
