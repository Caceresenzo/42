NAME = Colleen
CODE = $(NAME).c

all: $(NAME)

$(NAME): $(CODE)
	gcc -Wall -Werror -Wextra -o $(NAME) $(CODE)

clean:
	;

fclean: clean
	rm -f $(NAME)

re: clean all

test: all
	./$(NAME) > /tmp/output
	diff $(CODE) /tmp/output

diff-full: all
	./$(NAME) > /tmp/output
	diff --color --side-by-side $(CODE) /tmp/output

dev: all
	watch --interval 1 make diff-full

.PHONY: all clean fclean re test diff-full dev