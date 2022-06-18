NAME = libft_malloc.so
SRCS = library.c impl.c ft.c ft_printf.c block.c region.c viewer.c tune.c
OBJS = $(SRCS:.c=.o)
CC   = gcc
FLAGS = -Wall -Wextra -g3 -fPIC -fno-gnu-unique -rdynamic

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
	@gcc *.c -g3 -O0 -rdynamic
	@LD_PRELOAD=./libft_malloc.so ./a.out

test-no-preload: $(NAME)
	@gcc *.c -g3 -fsanitize=address
	@valgrind ./a.out

test-ls: $(NAME)
	#LD_PRELOAD=./libft_malloc.so ./track/coreutils-8.30/src/ls -la
	LD_PRELOAD=./libft_malloc.so ls -la

test-find: $(NAME)
	LD_PRELOAD=./libft_malloc.so $(shell which find) $(shell pwd)

test-find2: $(NAME)
	LD_PRELOAD=./libft_malloc.so findutils-4.9.0/find/find $(shell pwd)

test-sh: $(NAME)
	LD_PRELOAD=./libft_malloc.so $(shell which sh)

test-bash: $(NAME)
	LD_PRELOAD=./libft_malloc.so $(shell which bash)

test-python: $(NAME)
	LD_PRELOAD=./libft_malloc.so $(shell which python3) -c 'import os'

test-align: $(NAME)
	gcc helper/aligned.c
	LD_PRELOAD=./libft_malloc.so ./a.out

gdb: $(NAME)
	@gcc test.c
	gdb ./a.out

.PHONY: all bonus clean fclean re .c.o test
