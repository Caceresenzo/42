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
CFLAGS = -O0 -g3 -Wextra -Wall -Werror

all: $(TARGET)

.c.o:
	$(CC) -c $< -o $@ $(CPPFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all .c.o clean fclean re