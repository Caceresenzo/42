NAME = computor
SRCS = $(shell find source/ -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)
CC   = g++
FLAGS = -Isource -Wall -Wextra -Werror -g3 -std=c++98 -fsanitize=address

DEBUG = false

.cpp.o:
	${CC} ${FLAGS} -c $< -o ${<:.cpp=.o} -DDEBUG=$(DEBUG)

$(NAME): ${OBJS}
	${CC} ${FLAGS} $(OBJS) -o $(NAME)

all: $(NAME)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS)

re: fclean all

test-valid: $(NAME)
	@bash test/run.sh test/cases/valid 0

test-invalid: $(NAME)
	@bash test/run.sh test/cases/invalid 1

test: test-valid test-invalid

.PHONY: all bonus clean fclean re .cpp.o test test-valid test-invalid
