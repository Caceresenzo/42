# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 15:11:33 by ecaceres          #+#    #+#              #
#    Updated: 2019/08/13 15:11:34 by ecaceres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

NAME	=   libasm
LIB		=   $(NAME).a
SRCS	=	ft_strlen.s
OBJS	=	$(SRCS:.s=.o)
LIBC	= ar -rcs

%.o: $(PROJECT_ROOT)%.s
	nasm -f macho64 $< -o $@ 

$(NAME): ${OBJS}
	${LIBC} $(LIB) $(OBJS)

all: $(NAME)

clean:
	rm -fr $(NAME) $(OBJS)
    
fclean: clean
	$(RM) $(NAME)
    
re: fclean all

test: re
	gcc tests/*.c $(OBJS) -o test
	./test

.PHONY: all bonus clean fclean re