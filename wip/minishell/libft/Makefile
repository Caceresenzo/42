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

NAME	=   libft.a
SRCS	=	./ft_abs.c \
			./ft_atoi.c \
			./ft_bzero.c \
			./ft_calloc.c \
			./ft_chrmult.c \
			./ft_chrtostr.c \
			./ft_emptystr.c \
			./ft_fake_use.c \
			./ft_free_and_release.c \
			./ft_isalnum.c \
			./ft_isalpha.c \
			./ft_isascii.c \
			./ft_isdigit.c \
			./ft_isinstr.c \
			./ft_islower.c \
			./ft_isprint.c \
			./ft_isupper.c \
			./ft_iswspace.c \
			./ft_itoa.c \
			./ft_itoa_base.c \
			./ft_itoa_u_base.c \
			./ft_lsr.c \
			./ft_lstadd_back.c \
			./ft_lstadd_front.c \
			./ft_lstclear.c \
			./ft_lstdelone.c \
			./ft_lstiter.c \
			./ft_lstlast.c \
			./ft_lstmap.c \
			./ft_lstnew.c \
			./ft_lstsize.c \
			./ft_max.c \
			./ft_memccpy.c \
			./ft_memchr.c \
			./ft_memcmp.c \
			./ft_memcpy.c \
			./ft_memjoin.c \
			./ft_memmove.c \
			./ft_memset.c \
			./ft_min.c \
			./ft_putchar_fd.c \
			./ft_putendl_fd.c \
			./ft_putnbr_fd.c \
			./ft_putstr_fd.c \
			./ft_putuchar_fd.c \
			./ft_sort_comp.c \
			./ft_split.c \
			./ft_split_free.c \
			./ft_split_length.c \
			./ft_strchr.c \
			./ft_strcontain.c \
			./ft_strcmp.c \
			./ft_strdup.c \
			./ft_strjoin.c \
			./ft_strlcat.c \
			./ft_strlcpy.c \
			./ft_strlen.c \
			./ft_strmapi.c \
			./ft_strncmp.c \
			./ft_strnstr.c \
			./ft_strrchr.c \
			./ft_strtrim.c \
			./ft_substr.c \
			./ft_swap_double.c \
			./ft_swap_int.c \
			./ft_tolower.c \
			./ft_toupper.c \
			./ft_zero_if_neg.c \
			./get_next_line.c \
			./ft_str_isdigit.c \
			./ft_strjoin_free.c \
			./ft_strjoin_sided.c \
			./ft_atoi_base_insensitive.c \
			./ft_ishex.c \
			./ft_isoctal.c \
			./ft_base_resolve.c \
			./ft_base_validate.c \
			./ft_strjoin3.c \
			./ft_isquote.c

OBJS	= $(SRCS:.c=.o)
RM		= rm -f
LIBC	= ar -rcs
FLAGS	= -Wall -Wextra -Werror -O3 -g3
INCS	= .

.c.o :
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I${INCS}

$(NAME): ${OBJS}
	${LIBC} $(NAME) $(OBJS)

all: $(NAME)
    
fclean: clean
	$(RM) $(NAME) $(bonus)

clean:
	$(RM) -f $(OBJS) $(OBJS_B)
    
re: fclean all

.PHONY: all bonus clean fclean re .c.o