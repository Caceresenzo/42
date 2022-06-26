NAME = ft_nm
SOURCES = \
	source/main.c \
	source/main_help.c \
	source/flags.c \
	source/elf_header.c \
	source/elf_string.c \
	source/elf_symbol_decode.c \
	source/elf_section.c \
	source/elf_symbol.c \
	source/symbol.c \
	source/symbol_print.c \
	source/symbol_sort.c \
	source/message.c \
	source/list.c \
	source/ft.c
OBJECTS = $(SOURCES:.c=.o)
FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
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
	sh test/run.sh

test-corrupted: all
	make -C test/corrupted test

.PHONY: all bonus clean fclean re .c.o test
