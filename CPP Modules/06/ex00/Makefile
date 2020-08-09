# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/13 17:52:53 by ecaceres          #+#    #+#              #
#    Updated: 2020/07/13 17:52:53 by ecaceres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= convert
SRCS	= main.cpp Number.cpp
OBJS	= $(SRCS:.cpp=.o)
CPPC	= clang++
FLAGS	= -g3 -O0 -std=c++98 -Wall -Wextra -Werror

MULTI	= false
COLORED	= false

.cpp.o:
	$(CPPC) $(FLAGS) -c $< -o $@ -D MULTI=$(MULTI) -D COLORED=$(COLORED)

$(NAME): $(OBJS)
	$(CPPC) $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME) c
	@echo
	./$(NAME) a
	@echo
	./$(NAME) 0
	@echo
	./$(NAME) 42
	@echo
	./$(NAME) -42
	@echo
	./$(NAME) 0f
	@echo
	./$(NAME) 42f
	@echo
	./$(NAME) -42f
	@echo
	./$(NAME) 0.0f
	@echo
	./$(NAME) 42.0f
	@echo
	./$(NAME) -42.0f
	@echo
	./$(NAME) 4.2f
	@echo
	./$(NAME) -4.2f
	@echo
	./$(NAME) 42.f
	@echo
	./$(NAME) -42.f
	@echo
	./$(NAME) 0.0
	@echo
	./$(NAME) 42.0
	@echo
	./$(NAME) -42.0
	@echo
	./$(NAME) 4.2
	@echo
	./$(NAME) -4.2
	@echo
	./$(NAME) 42.
	@echo
	./$(NAME) -42.
	@echo
	./$(NAME) inff
	@echo
	./$(NAME) -inff
	@echo
	./$(NAME) nanf
	@echo
	./$(NAME) inf
	@echo
	./$(NAME) -inf
	@echo
	./$(NAME) nan
	@echo
	./$(NAME) +0
	@echo
	./$(NAME) -0
	@echo
	./$(NAME) 42.0042

test-error: all
	! ./$(NAME) ""
	@echo
	! ./$(NAME) +
	@echo
	! ./$(NAME) ++
	@echo
	! ./$(NAME) -
	@echo
	! ./$(NAME) --
	@echo
	! ./$(NAME) 0..0
	@echo
	! ./$(NAME) 0..
	@echo
	! ./$(NAME) ..0
	@echo
	! ./$(NAME) +nan
	@echo
	! ./$(NAME) +nanf
	@echo
	! ./$(NAME) -nan
	@echo
	! ./$(NAME) -nanf
	@echo
	! ./$(NAME) aa
	@echo
	! ./$(NAME) 0123a

test-ascii: all
	echo Here is your ascii: ; for i in $$(seq 32 126); do ./$(NAME) $$i | sed -E "s/[[:cntrl:]]\[[0-9]{1,3}m//g" | grep char | sed "s/char: '\(.*\)'/\1/g" | tr -d '\n'; done

test-all: all test test-error test-ascii

test-break: all
	@zsh -c 'for i in $$(seq 310 1); do echo ---- Current: -$$i; ./$(NAME) -1$$(printf "0%.0s" {1..$$i}); echo; done;'
	@zsh -c 'echo ---- Current: -1; ./$(NAME) -1; echo;'
	@zsh -c 'echo ---- Current: -0; ./$(NAME) -0; echo;'
	@zsh -c 'echo ---- Current: 0; ./$(NAME) 0; echo;'
	@zsh -c 'echo ---- Current: 1; ./$(NAME) 1; echo;'
	@zsh -c 'for i in $$(seq 1 310); do echo ---- Current: $$i; ./$(NAME) 1$$(printf "0%.0s" {1..$$i}); echo; done;'

.PHONY: all re clean fclean .cpp.o test test-error test-ascii test-break
