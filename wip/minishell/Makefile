NAME = minishell

LIB = libft/libft.a
PRINTF = ft_printf/libftprintf.a

INC = minishell.h

FLAGS = -Wall -Wextra -Werror -g3 -O0

SRCS =		argument_builder.c \
			argument_builder_debugger.c \
			arraylist_add.c \
			arraylist_add_all.c \
			arraylist_clear.c \
			arraylist_create.c \
			arraylist_destroy.c \
			arraylist_get.c \
			arraylist_grow.c \
			arraylist_index_of.c \
			arraylist_init.c \
			arraylist_remove.c \
			arraylist_remove_at.c \
			buildin_matcher.c \
			builtin.c \
			builtin_error.c \
			builtin_handler_cd.c \
			builtin_handler_echo.c \
			builtin_handler_env.c \
			builtin_handler_exit.c \
			builtin_handler_export.c \
			builtin_handler_pwd.c \
			builtin_handler_unset.c \
			env_array.c \
			env_compare.c \
			env_dump.c \
			env_finalize.c \
			env_get.c \
			env_initializer.c \
			env_loader.c \
			env_set.c \
			env_unset.c \
			env_var_creator.c \
			env_var_free.c \
			env_var_validity.c \
			evaluator_env_var.c \
			evaluator_escape_backslash.c \
			evaluator_next.c \
			evaluator_quote_double.c \
			evaluator_quote_single.c \
			evaluator_tilde.c \
			evaluator_token.c \
			evaluator_utilities.c \
			executor_builder.c \
			main.c \
			minishell.c \
			minishell_error.c \
			minishell_evaluator.c \
			minishell_evaluator_builtin.c \
			minishell_exit.c \
			minishell_initialize.c \
			minishell_pre_loop.c \
			minishell_process_kill.c \
			minishell_prompt.c \
			minishell_signals.c \
			process_debugger.c \
			process_destroy.c \
			process_execute.c \
			process_file_finder.c \
			signal_handler_interrupt.c \
			signal_handler_quit.c \
			token.c \
			token_arg_group.c \
			token_io_file.c \
			utility_find_home.c

OBJ = $(SRCS:%.c=%.o)

%.o: %.c
	gcc -I $(INC) $(FLAGS) -c $< -o $@

all: $(NAME)

makelib:
	@$(MAKE) -C libft
	@$(MAKE) -C ft_printf

$(NAME) : $(OBJ) | makelib
	gcc -I $(INC) $(OBJ) $(LIB) $(PRINTF) -o $(NAME) 
	chmod +x $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	norminette *.[ch]
	norminette */*.[ch]

.PHONY: all makelib clean fclean re norm
