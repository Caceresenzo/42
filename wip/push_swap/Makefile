TARGET_CHECKER = checker
TARGET_PUSH_SWAP = push_swap

SOURCES = \
	src/operation_call.c \
	src/operation_find.c \
	src/op_impl_push.c \
	src/op_impl_reverse_rotate.c \
	src/op_impl_rotate.c \
	src/op_impl_swap.c \
	src/stacks_validate.c \
	src/stack_from_argv.c

include libft/module.mk
include libstack/module.mk

SOURCE_CHECKER = src/main_checker.c
SOURCE_PUSH_SWAP = src/main_push_swap.c

OBJECTS = $(SOURCES:.c=.o)
OBJECT_CHECKER = $(SOURCE_CHECKER:.c=.o)
OBJECT_PUSH_SWAP = $(SOURCE_PUSH_SWAP:.c=.o)

LIBRARIES = libstack libft

RM = rm -f

COMPILER = gcc
COMPILER_FLAGS = -g3 -Wall -Werror -Wextra

LINKER = gcc
LINKER_FLAGS = -g3 -Wall -Werror -Wextra -o

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) -o $@ -c $<

all: $(TARGET_CHECKER) $(TARGET_PUSH_SWAP)

$(TARGET_CHECKER): $(OBJECTS) $(OBJECT_CHECKER)
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET_CHECKER) $(OBJECTS) $(OBJECT_CHECKER)

$(TARGET_PUSH_SWAP): $(OBJECTS) $(OBJECT_PUSH_SWAP)
	$(COMPILER) $(COMPILER_FLAGS) -o $(TARGET_PUSH_SWAP) $(OBJECTS) $(OBJECT_PUSH_SWAP)

clean:
	$(RM) $(OBJECT_CHECKER) $(OBJECTS) $(OBJECT_PUSH_SWAP)

fclean: clean
	$(RM) $(TARGET_CHECKER) $(TARGET_PUSH_SWAP)

re: fclean all

.SUFFIXES: .c .o
.PHONY: all clean fclean re libs