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

NAME	= ex02
SRCS	= main.cpp Base.cpp A.cpp B.cpp C.cpp Another.cpp
OBJS	= $(SRCS:.cpp=.o)
CPPC	= clang++
FLAGS	= -g3 -O0 -std=c++98 -Wall -Wextra -Werror

.cpp.o:
	$(CPPC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CPPC) $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean .cpp.o
