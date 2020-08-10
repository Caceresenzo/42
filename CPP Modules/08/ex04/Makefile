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
	./$(NAME) "3" && echo
	./$(NAME) "(3)" && echo
	./$(NAME) "((1 + 4) * 2)" && echo
	./$(NAME) "((1 + 4))" && echo
	./$(NAME) "3 + ((1 + 4) * 2) / 10" && echo
	./$(NAME) "3 + ((1 + 4) * 2) - 1" && echo
	./$(NAME) "3 + 3 * 9" && echo
	./$(NAME) "-2147483648" && echo
	./$(NAME) "2147483647" && echo
	./$(NAME) "-2147483648 - 1" && echo
	./$(NAME) "2147483647 + 1" && echo
	./$(NAME) "(((((((((((((((((5)))))))))))))))))" && echo
	./$(NAME) "(((((((((((((((((5)+7))+8))))*9)))))/3)))))" && echo

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
	! ./$(NAME) "5(6*7)" && echo
	! ./$(NAME) "(6*7)5" && echo
	! ./$(NAME) "5/0" && echo
	
test-leaks: all
	@printf "EXPRESSION \033[67G DEFINETLY LOST  \033[100G INDIRECTLY LOST \n"
	@cat Makefile | \
		grep -oE "\"(.*)\" && echo$$" \
		| awk -F\" '{print $$2}' \
		| while read line; do  \
			printf "%s \033[67G" "$$line"; \
			valgrind ./$(NAME) "$$line" 2>&1 > /tmp/cpp_08_valgrind_out \
			| tee /tmp/cpp_08_valgrind_out \
			| grep "definitely lost" \
			| awk -F: '{print $$2}' \
			| tr -d '\n' || true; \
			printf "\033[100G"; \
			cat /tmp/cpp_08_valgrind_out \
			| grep "indirectly lost" \
			| tr -d '\n' \
			| awk -F: '{print $$2}'; \
			printf "\033[125G"; \
			cat /tmp/cpp_08_valgrind_out \
			| grep "All heap blocks were freed -- no leaks are possible" \
			| tr -d '\n'; \
			echo; \
		done

test-break-valid: all
	valgrind --leak-check=full ./$(NAME) "$$(python3 -c 'print("(" * 2500 + "5" + ") + 1" * 2500)')"
	
test-break-invalid: all
	! valgrind --leak-check=full ./$(NAME) "$$(python3 -c 'print("(" * 2500 + "5" + ") + 1" * 2499)')"

.PHONY: all re clean fclean .cpp.o test test-error test-leaks test-break-valid test-break-invalid
