NAME = computor
SRCS = $(shell find source/ -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)
CC   = g++
FLAGS = -Isource -Wall -Wextra -Werror -g3 #-fsanitize=address

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

test: all
	@bash test/run.sh test/cases/valid 0
	@bash test/run.sh test/cases/invalid 1

.PHONY: all bonus clean fclean re .cpp.o test