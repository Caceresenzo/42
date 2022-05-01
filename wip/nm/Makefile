NAME = ft_nm
SRCS = elf_header.c elf_string.c elf_symbol_decode.c list.c main_help.c elf_section.c elf_symbol.c flags.c main.c symbol_helper.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${CC} $(OBJS) -o $(NAME)

all: $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

re: fclean all

simple-test: all
	bash test/compile-and-run.sh

advanced-test: all
	bash test/test.sh /lib32/libpthread.so.0

all-test: simple-test advanced-test

.PHONY: all bonus clean fclean re .c.o simple-test advanced-test all-test