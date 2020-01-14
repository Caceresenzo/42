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

NAME	=   libasm.a
SRCS	=	ft_strlen.s \
			ft_strcpy.s \
			ft_strcmp.s \
			ft_write.s \
			ft_read.s \
			ft_strdup.s
SRCS_B	=	ft_atoi_base.s \
			ft_list_push_front.s \
			ft_list_size.s \
			ft_list_sort.s \
			ft_list_remove_if.s
OBJS	=	$(SRCS:.s=.o)
OBJS_B	=	$(SRCS_B:.s=.o)
NASM	= nasm
LIBC	= ar -rcs

.s.o:
	${NASM} -lc -f macho64 $< -o $@ 

$(NAME): ${OBJS}
	${LIBC} $(NAME) $(OBJS)

all: $(NAME)

bonus: ${OBJS} $(OBJS_B)
	${LIBC} $(NAME) $(OBJS) $(OBJS_B)

clean:
	rm -f $(NAME) $(OBJS) $(OBJS_B)
    
fclean: clean
	$(RM) $(NAME)
    
re: fclean all

test: fclean bonus
	gcc -include libasm.h debug/*.c tests/*.c tests/*/*.c $(OBJS) $(OBJS_B) -g3 -o test -D NOTIFY=1 -D MORE_DEBUG=0
	./test || true
#	gcc -include libasm.h tests/*.c $(OBJS) -g3 -o test -D NOTIFY=0
#	./test
#	@echo ""
#	./test | hexdump

.PHONY: all bonus clean fclean re test
