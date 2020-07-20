# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/13 17:52:53 by ecaceres          #+#    #+#              #
#    Updated: 2020/07/13 17:52:53 by ecaceres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ex04
SRCS	=	main.cpp \
			NumericToken.cpp \
			OperatorToken.cpp \
			ParenthesisCloseToken.cpp \
			ParenthesisOpenToken.cpp \
			PostfixConvertor.cpp \
			Token.cpp \
			TokenParser.cpp
OBJS	= $(SRCS:.cpp=.o)
CPPC	= clang++
FLAGS	= -g3 -O0 -std=c++98 -Wall -Wextra -Werror

.cpp.o:
	$(CPPC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CPPC) $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)  "3" && echo
	./$(NAME)  "(3)" && echo
	./$(NAME)  "((1 + 4) * 2)" && echo
	./$(NAME)  "((1 + 4))" && echo
	./$(NAME)  "3 + ((1 + 4) * 2) / 10" && echo
	./$(NAME)  "3 + ((1 + 4) * 2) - 1" && echo
	./$(NAME)  "3 + 3 * 9" && echo
	./$(NAME)  "-2147483648" && echo
	./$(NAME)  "2147483647" && echo
	./$(NAME)  "-2147483648 - 1" && echo
	./$(NAME)  "2147483647 + 1" && echo
	./$(NAME)  "(((((((((((((((((5)))))))))))))))))" && echo
	./$(NAME)  "(((((((((((((((((5)+7))+8))))*9)))))/3)))))" && echo

test-error: all
	! ./$(NAME) "+" && echo
	! ./$(NAME) "(" && echo
	! ./$(NAME) ")" && echo
	! ./$(NAME) "()" && echo
	! ./$(NAME) "5+" && echo
	! ./$(NAME) "5(" && echo
	! ./$(NAME) "5)" && echo
	! ./$(NAME) "5()" && echo
	! ./$(NAME) "5+(" && echo
	! ./$(NAME) "5+(" && echo
	! ./$(NAME) "5+)" && echo
	! ./$(NAME) "5+()" && echo
	! ./$(NAME) "5+(6))" && echo
	! ./$(NAME) "5+((6)" && echo
	! ./$(NAME) "5++6" && echo
	! ./$(NAME) "5 6" && echo
	! ./$(NAME) "5 6 7" && echo
	! ./$(NAME) "5+6 7" && echo
	! ./$(NAME) "5+(6 7" && echo
	! ./$(NAME) "5/0" && echo

.PHONY: all re clean fclean .cpp.o
