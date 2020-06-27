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

NAME		= cato9tails
SRCS		=	./main.cpp
OBJS		= $(SRCS:.cpp=.o)
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror -std=c++98
COMPILER	= clang++
P_NAME		= ${NAME}

.cpp.o:
	${COMPILER} ${FLAGS} -D PROGRAM_NAME=\"${P_NAME}\" -c $< -o ${<:.cpp=.o}

$(NAME): ${OBJS}
	${COMPILER} ${FLAGS} $(OBJS) -o $(NAME)

all: $(NAME)
    
fclean: clean
	$(RM) $(NAME)
    
clean:
	$(RM) -f $(OBJS) $(OBJS_B)
    
re: fclean all

test:
	make re P_NAME=cat
	
	@sh tests/do_test.sh "Common"		"A simple file"						"0"		Makefile
	@sh tests/do_test.sh "Common"		"2 simple file"						"0"		Makefile main.cpp
	@sh tests/do_test.sh "Common"		"A binary file"       				"0"		main.o
	@sh tests/do_test.sh "Common"		"2 binary file"       				"0"		main.o cato9tails
	@sh tests/do_test.sh "Common"		"Invalid file"						"0"		/i/do/not/exists
	@sh tests/do_test.sh "Common"		"Multiple invalid file"				"0"		/i/do/not/exists /i/do/not/exists /i/do/not/exists
	@sh tests/do_test.sh "Common"		"Invalid file in middle"			"0"		Makefile /i/do/not/exists main.cpp
	@sh tests/do_test.sh "Common"		"/tmp folder"						"0"		/tmp
	@sh tests/do_test.sh "Common"		"/goinfre folder"					"0"		/goinfre
	@sh tests/do_test.sh "Common"		"Current folder"					"0"		./
	@sh tests/do_test.sh "Common"		"Piped word"						"1"		"Hello World From Cat"
	@sh tests/do_test.sh "Common"		"Piped word but with file"			"1"		"Hello World From Cat" Makefile
	@sh tests/do_test.sh "Common"		"Piped word but with multiple file"	"1"		"Hello World From Cat" Makefile main.cpp
	@sh tests/do_test.sh "Common"		"Piped word but with invalid file"	"1"		"Hello World From Cat" /i/do/not/exists
	
	@touch the_hidden_one ; chmod 000 the_hidden_one;
	@sh tests/do_test.sh "Common"		"000 perm file"						"0"		the_hidden_one
	@chmod 777 the_hidden_one ; rm -f the_hidden_one;
	
	@mkdir the_hidden_one ; chmod 000 the_hidden_one;
	@sh tests/do_test.sh "Rare"		"000 perm folder"						"0"		the_hidden_one
	@chmod 777 the_hidden_one ; rm -rf the_hidden_one;
	
	@sh tests/do_test.sh "Rare"		"Empty file"							"0"		"\"\""


.PHONY: all clean fclean re .cpp.o test
