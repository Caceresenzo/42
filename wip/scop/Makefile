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

EXTRA_OPTIONS			=

.cpp.o: library/glew
	${COMPILER} ${FLAGS} -c $< -o ${<:.cpp=.o}

$(TARGET): library/glew ${OBJECTS}
	${COMPILER} ${FLAGS} $(OBJECTS) $(LIBRARIES) -o $(TARGET)

all: $(TARGET)
    
fclean: clean
	rm -f $(TARGET)
    
clean:
	rm -f $(OBJECTS)
    
re: fclean all

library/glew:
	cd library && make glew

run-cube: all
	./scop $(EXTRA_OPTIONS) assets/models/cube.obj

run-ft: all
	./scop $(EXTRA_OPTIONS) assets/models/42.obj assets/models/my-little-pony.bmp

run-teapot: all
	./scop $(EXTRA_OPTIONS) assets/models/teapot.obj assets/models/capsule.bmp --no-culling

run-teapot2: all
	./scop $(EXTRA_OPTIONS) assets/models/teapot.obj assets/models/capsule.bmp --no-culling

run-capsule: all
	./scop $(EXTRA_OPTIONS) assets/models/capsule.obj assets/models/capsule.bmp

.PHONY: all clean fclean re .cpp.o
