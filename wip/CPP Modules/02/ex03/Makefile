# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 15:11:33 by ecaceres          #+#    #+#              #
#    Updated: 2019/08/13 15:11:34 by ecaceres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= eval_expr
SRCS		= ArrayList.cpp Fixed.cpp Lexer.cpp NumberToken.cpp Parser.cpp Token.cpp Utils.cpp main.cpp TokenReader.cpp Evaluator.cpp
OBJS		= $(SRCS:.cpp=.o)
RM			= rm -f
FLAGS		= -g3 -O0 -std=c++98 -Wall -Wextra -Werror
COMPILER	= clang++
P_NAME		= ${NAME}

.cpp.o:
	${COMPILER} ${FLAGS} -c $< -o ${<:.cpp=.o}

$(NAME): ${OBJS}
	${COMPILER} ${FLAGS} $(OBJS) -o $(NAME)

all: $(NAME)
    
fclean: clean
	$(RM) $(NAME)
    
clean:
	$(RM) -f $(OBJS) $(OBJS_B)
    
re: fclean all

test: all
	./eval_expr ""
	@test $$(./eval_expr "") = '0'
	
	./eval_expr "42"
	@test $$(./eval_expr "42") = '42'
	
	./eval_expr "5*6"
	@test $$(./eval_expr "5*6") = '30'
	
	./eval_expr "(18.18 + 3.03) * 2"
	@test $$(./eval_expr "(18.18 + 3.03) * 2") = '42.4219'
	
	./eval_expr "(1)"
	@test $$(./eval_expr "(1)") = '1'
	
	./eval_expr "(1.23456)"
	@test $$(./eval_expr "1.23456") = '1.23438'
	
	./eval_expr "   2 + 2 * 5   "
	@test $$(./eval_expr "    2 + 2 * 5    ") = '12'
	
	./eval_expr "(((((((((((5)))))))) + 3)) * 3) * 20"
	@test $$(./eval_expr "(((((((((((5)))))))) + 3)) * 3) * 20") = '480'
	
	./eval_expr "((((1 + (((((((5)))))))) + 3)) * 3) * 20"
	@test $$(./eval_expr "((((1 + (((((((5)))))))) + 3)) * 3) * 20") = '540'
		./eval_expr " 21 + 21 " 
	@test $$(./eval_expr " 21 + 21 ") = '42' 

	./eval_expr " 6*7 " 
	@test $$(./eval_expr " 6*7 ") = '42' 

	./eval_expr " 20 + 1 + (10*2) + 1 " 
	@test $$(./eval_expr " 20 + 1 + (10*2) + 1 ") = '42'

	./eval_expr " 100/10 " 
	@test $$(./eval_expr " 100/10 ") = '10' 

	./eval_expr " 12*12 " 
	@test $$(./eval_expr " 12*12 ") = '144' 

	./eval_expr " 2 * 10 " 
	@test $$(./eval_expr " 2 * 10 ") = '20' 

	./eval_expr " 100 * 9 " 
	@test $$(./eval_expr " 100 * 9 ") = '900' 

	./eval_expr " 11.02 - 9.1 " 
	@test $$(./eval_expr " 11.02 - 9.1 ") = '1.91797' 

	./eval_expr " 29.1+39 " 
	@test $$(./eval_expr " 29.1+39 ") = '68.1016' 
	
	

test-error:
	! ./eval_expr "()"
	! ./eval_expr "+"
	! ./eval_expr "1 +"
	! ./eval_expr "+ 1"
	! ./eval_expr "1 ++ 1"
	! ./eval_expr "1 1"
	! ./eval_expr "()()"
	! ./eval_expr "(1)(1)"
	! ./eval_expr "(11)1"
	! ./eval_expr "((11)1)"
	! ./eval_expr "((11) / 0)"
	! ./eval_expr "1 1"
	! ./eval_expr "(1) 1"
	! ./eval_expr "1 / 0"
	! ./eval_expr "1 / (5 - 5)"
	! ./eval_expr "Hello"
	! ./eval_expr "1 / d4"
	! ./eval_expr "("
	! ./eval_expr ")"
	! ./eval_expr "+"
	! ./eval_expr "-"
	! ./eval_expr "/"
	! ./eval_expr "*"
	! ./eval_expr "*/"
	! ./eval_expr "      ("
	! ./eval_expr "      )"
	! ./eval_expr "      +"
	! ./eval_expr "      -"
	! ./eval_expr "      /"
	! ./eval_expr "      *"
	! ./eval_expr "      */"
	! ./eval_expr "$$(head -n 1 /dev/random)"

test-all: test test-error

.PHONY: all clean fclean re .cpp.o .test