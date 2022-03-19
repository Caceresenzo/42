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

PROJECT_ROOT			= $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

TARGET					= scop
SOURCES					= $(shell find . -name "*.cpp" -a -not -name "*test*")

OBJECTS					= $(SOURCES:.cpp=.o)

COMPILER				= g++

FRAMEWORKS				= 
FLAGS					= -Wall -Wextra -Werror -g3 -O0 -I. # -fsanitize=address
LIBRARIES				= -lGL -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lGLEW

.cpp.o:
	${COMPILER} ${FLAGS} -c $< -o ${<:.cpp=.o}

$(TARGET): ${OBJECTS}
	${COMPILER} ${FLAGS} $(foreach framework,$(FRAMEWORKS),-framework $(framework)) $(OBJECTS) $(LIBRARIES) -o $(TARGET)

all: $(TARGET)
    
fclean: clean
	rm -f $(TARGET)
    
clean:
	rm -f $(OBJECTS)
    
re: fclean all

.PHONY: all clean fclean re .cpp.o
