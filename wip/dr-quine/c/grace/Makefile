NAME = Grace
CODE = $(NAME).c
OUTPUT = $(NAME)_kid.c

all: $(NAME)

$(NAME): $(CODE)
	gcc -Wall -Werror -Wextra -o $(NAME) $(CODE)

clean:
	;

fclean: clean
	rm -f $(NAME)

re: clean all

test: all
	./$(NAME)
	diff $(CODE) $(OUTPUT)

diff-full: all
	./$(NAME) > /tmp/output
	diff --color --side-by-side $(CODE) $(OUTPUT)

dev: all
	watch --interval 1 make diff-full

.PHONY: all clean fclean re test diff-full dev