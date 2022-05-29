NAME = computorv1
SRCS = $(shell find -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)
CC   = g++
FLAGS = -I. -Wall -Wextra -Werror -g3 #-fsanitize=address

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

.PHONY: all bonus clean fclean re .cpp.o