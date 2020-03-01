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

NAME		= libftprintf.a
LIBFT		= ../libft
LIBFT_LIB	= ../libft/libft.a
SRCS		=	./ft_dprintf.c \
				./ft_printf.c \
				./ft_printf_flag_handler.c \
				./ft_printf_flag_initializer.c \
				./ft_printf_flag_parser.c \
				./ft_printf_flag_validator.c \
				./ft_printf_format_char.c \
				./ft_printf_format_decimal.c \
				./ft_printf_format_empty.c \
				./ft_printf_format_hex_int.c \
				./ft_printf_format_octal_int.c \
				./ft_printf_format_pointer.c \
				./ft_printf_format_pourcent.c \
				./ft_printf_format_string.c \
				./ft_printf_format_uint.c \
				./ft_printf_formatter.c \
				./ft_printf_formatter_registry.c \
				./ft_printf_handler.c \
				./ft_printf_is_flag_char.c \
				./ft_printf_padder.c \
				./ft_printf_putchar.c \
				./ft_printf_putstr.c \
				./ft_printf_which_unit.c \
				./ft_vdprintf.c \
				./ft_vprintf.c
OBJS		= $(SRCS:.c=.o)
RM			= rm -f
LIBC		= ar -rcs
FLAGS		= -Wall -Wextra -Werror -O3 -g3
INCS		= .
COMPILER	= cc

.c.o:
	${COMPILER} ${FLAGS} -c $< -o ${<:.c=.o} -I${INCS}

$(NAME): ${OBJS}
	make all -C $(LIBFT)/
	cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	${LIBC} $(NAME) $(OBJS)

all: $(NAME)
    
fclean: clean
	$(RM) $(NAME) $(bonus)
	make fclean -C $(LIBFT)
    
clean:
	$(RM) -f $(OBJS) $(OBJS_B)
	make clean -C $(LIBFT)
    
re: fclean all

bonus: all

.PHONY: all clean fclean re .c.o bonus