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

SOURCES = $(shell find -type f -name \*.c)
OBJECTS = $(SOURCES:.c=.o)

TARGET = ft_ssl

CC = gcc
CFLAGS = -O0 -g3 -Wextra -Wall -Werror -fsanitize=address

all: $(TARGET)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

test-md5: all
	bash test/run.sh md5

test-sha256: all
	bash test/run.sh sha256

test: test-md5 test-sha256

scenario-md5: all
	bash test/scenario.sh md5

scenario-sha256: all
	bash test/scenario.sh sha256

incremental-md5: all
	bash test/incremental.sh md5

incremental-sha256: all
	bash test/incremental.sh sha256

.PHONY: all .c.o clean fclean re