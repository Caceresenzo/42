TARGET_CHECKER = checker
TARGET_PUSH_SWAP = push_swap

SOURCES = \
	src/algorithm/action.c \
	src/algorithm/find.c \
	src/algorithm/run.c \
	src/algorithm/impl/smallest.c \
	src/algorithm/impl/insertion.c \
	src/helper/stacks_validate.c \
	src/helper/stack_from_argv.c \
	src/helper/stack_is_sorted.c \
	src/operation/call.c \
	src/operation/find.c \
	src/operation/impl/push.c \
	src/operation/impl/reverse_rotate.c \
	src/operation/impl/rotate.c \
	src/operation/impl/swap.c \
	src/solver/solver.c

include libft/module.mk
include libstack/module.mk
include liblist/module.mk

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

norm:
	norminette $(SOURCES)

.SUFFIXES: .c .o
.PHONY: all clean fclean re norm