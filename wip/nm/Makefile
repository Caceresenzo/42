NAME = ft_nm
SRCS = elf_header.c elf_string.c elf_symbol_decode.c list.c main_help.c elf_section.c elf_symbol.c flags.c main.c symbol_helper.c message.c ft.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${CC} ${FLAGS} $(OBJS) -o $(NAME)

all: $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

re: fclean all

test: all
	sh tests/run.sh

.PHONY: all bonus clean fclean re .c.o test