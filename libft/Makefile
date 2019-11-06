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

C_YELLOW_B=\033[1;33m
C_LIGHT_RED_B=\033[0;91m
C_WHITE=\033[0;97m
C_RESET=\033[0;39m

SRCS	=	src/ft_atoi.c \
			src/ft_bzero.c \
			src/ft_calloc.c \
			src/ft_isalnum.c \
			src/ft_isalpha.c \
			src/ft_isascii.c \
			src/ft_isdigit.c \
			src/ft_isprint.c \
			src/ft_itoa.c \
			src/ft_memccpy.c \
			src/ft_memchr.c \
			src/ft_memcmp.c \
			src/ft_memcpy.c \
			src/ft_memmove.c \
			src/ft_memset.c \
			src/ft_putchar_fd.c \
			src/ft_putendl_fd.c \
			src/ft_putnbr_fd.c \
			src/ft_putstr_fd.c \
			src/ft_split.c \
			src/ft_strchr.c \
			src/ft_strdup.c \
			src/ft_strjoin.c \
			src/ft_strlcat.c \
			src/ft_strlcpy.c \
			src/ft_strlen.c \
			src/ft_strmapi.c \
			src/ft_strncmp.c \
			src/ft_strnstr.c \
			src/ft_strrchr.c \
			src/ft_strtrim.c \
			src/ft_substr.c \
			src/ft_tolower.c \
			src/ft_toupper.c 
SRCS_B = ${SRCS} \
			src-bonus/ft_lstadd_back_bonus.c \
			src-bonus/ft_lstadd_front_bonus.c \
			src-bonus/ft_lstclear_bonus.c \
			src-bonus/ft_lstdelone_bonus.c \
			src-bonus/ft_lstiter_bonus.c \
			src-bonus/ft_lstlast_bonus.c \
			src-bonus/ft_lstmap_bonus.c \
			src-bonus/ft_lstnew_bonus.c \
			src-bonus/ft_lstsize_bonus.c 

OBJS	= ${SRCS:.c=.o}
OBJS_B	= ${SRCS_B:.c=.o}
INCS	= .
NAME	= libft.a
CC		= gcc
LIBC	= ar rc
LIBR	= ranlib
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCS}

${NAME} : ${OBJS}
	#${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	${LIBC} ${NAME} ${OBJS}
	${LIBR} ${NAME}

all : ${NAME}

bonus : ${OBJS_B}
	#${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	${LIBC} ${NAME} ${OBJS_B}
	${LIBR} ${NAME}

clean :
	${RM} ${OBJS_B}

fclean : clean
	${RM} ${NAME}

norm :
	@norminette *.[ch]
	@norminette */*.[ch]

re : fclean all

test :
	echo ${SRCS_B:.c=.o}

.PHONY: all bonus clean fclean re .c.o test