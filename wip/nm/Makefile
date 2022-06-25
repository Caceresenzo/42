NAME = ft_nm
SOURCES = \
	main.c \
	main_help.c \
	flags.c \
	elf_header.c \
	elf_string.c \
	elf_symbol_decode.c \
	elf_section.c \
	elf_symbol.c \
	symbol.c \
	symbol_print.c \
	symbol_sort.c \
	message.c \
	list.c \
	ft.c
OBJECTS = $(SOURCES:.c=.o)
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CC = clang

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJECTS}
	${CC} ${FLAGS} $(OBJECTS) -o $(NAME)

all: $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJECTS)

re: fclean all

test: all
	sh tests/run.sh

.PHONY: all bonus clean fclean re .c.o test
