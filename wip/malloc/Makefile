NAME = libft_malloc.so
SRCS = library.c ft.c ft_printf.c block.c region.c
OBJS = $(SRCS:.c=.o)
CC   = gcc
FLAGS = -Wall -Wextra -g3 -fPIC -fno-gnu-unique

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	gcc $(OBJS) -o $(NAME) -fPIC -shared -fno-gnu-unique

all: $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

re: fclean all

test: $(NAME)
	@gcc *.c
	@LD_PRELOAD=./libft_malloc.so ./a.out

test-no-preload: $(NAME)
	@gcc *.c -g3
	@valgrind ./a.out

test-ls: $(NAME)
	LD_PRELOAD=./libft_malloc.so $(shell which ls)

test-find: $(NAME)
	LD_PRELOAD=./libft_malloc.so $(shell which find) $(shell pwd)

test-sh: $(NAME)
	LD_PRELOAD=./libft_malloc.so $(shell which sh)

test-bash: $(NAME)
	LD_PRELOAD=./libft_malloc.so $(shell which bash)

gdb: $(NAME)
	@gcc test.c
	gdb ./a.out

.PHONY: all bonus clean fclean re .c.o
