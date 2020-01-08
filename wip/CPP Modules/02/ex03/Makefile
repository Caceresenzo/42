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
SRCS		=	./Evaluator.cpp ./Fixed.cpp ./Lexer.cpp ./Parser.cpp ./Token.cpp ./Utils.cpp ./main.cpp
OBJS		= $(SRCS:.cpp=.o)
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror
COMPILER	= clang++
P_NAME		= ${NAME}

.cpp.o:
	${COMPILER} ${FLAGS} -c $< -o ${<:.cpp=.o}

$(NAME): ${OBJS}
	make -C libft
	${COMPILER} ${FLAGS} ./libft/libft.a  $(OBJS) -o $(NAME)

all: $(NAME)
    
fclean: clean
	make fclean -C libft
	$(RM) $(NAME)
    
clean:
	make clean -C libft
	$(RM) -f $(OBJS) $(OBJS_B)
    
re: fclean all

test: all
	./eval_expr ""
	./eval_expr "42"
	./eval_expr "5*6"
	./eval_expr "(18.18 + 3.03) * 2"
	./eval_expr "()"
	./eval_expr "(1)"
	./eval_expr "(1.23456)"
	./eval_expr " 2 + 2 * 5"
	
	./eval_expr "+" || true
	./eval_expr "1 +" || true
	./eval_expr "+ 1" || true
	./eval_expr "1 ++ 1" || true
	./eval_expr "1 1" || true
	./eval_expr "()()" || true
	./eval_expr "(1)(1)" || true
	./eval_expr "1 1" || true
	./eval_expr "(1) 1" || true
	./eval_expr "1 / 0" || true
	./eval_expr "1 / (5 - 5)" || true
	./eval_expr "Hello" || true
	./eval_expr "1 / d4" || true

.PHONY: all clean fclean re .cpp.o .test