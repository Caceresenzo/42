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

NAME	= mindopen
SRCS	=	CommandFactory.cpp \
			commands/DecrementDataCommand.cpp \
			commands/DecrementDataPointerCommand.cpp \
			commands/IncrementDataCommand.cpp \
			commands/IncrementDataPointerCommand.cpp \
			commands/InputDataCommand.cpp \
			commands/OutputDataCommand.cpp \
			commands/WhileCloseCommand.cpp \
			commands/WhileOpenCommand.cpp \
			Context.cpp \
			ICommand.cpp \
			main.cpp
OBJS	= $(SRCS:.cpp=.o)
CPPC	= clang++
FLAGS	= -g3 -O0 -std=c++98 -Wall -Wextra -Werror

BRAINFUCK_CHARSET = false

.cpp.o:
	$(CPPC) $(FLAGS) -c $< -o $@ -D BRAINFUCK_CHARSET=$(BRAINFUCK_CHARSET)

$(NAME): $(OBJS)
	$(CPPC) $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean .cpp.o
