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
SOURCES					= $(shell find source/ -name "*.cpp")

OBJECTS					= $(SOURCES:.cpp=.o)

COMPILER				= g++

FLAGS					= -Wall -Wextra -Werror -g3 -O0 -Isource/ -I./library/glew # -fsanitize=address
LIBRARIES				= -lGL -lGLU -lglfw -lX11 -lXxf86vm -lXrandr -lpthread ./library/glew/libGLEW.a

.cpp.o: glew
	${COMPILER} ${FLAGS} -c $< -o ${<:.cpp=.o}

$(TARGET): glew ${OBJECTS}
	${COMPILER} ${FLAGS} $(OBJECTS) $(LIBRARIES) -o $(TARGET)

all: $(TARGET)
    
fclean: clean
	rm -f $(TARGET)
    
clean:
	rm -f $(OBJECTS)
    
re: fclean all

glew:
	cd library && make

.PHONY: all clean fclean re .cpp.o
