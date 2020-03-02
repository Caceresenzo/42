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

COLOR_RESET						= \x1b[0m
COLOR_LIGHT_GREEN				= \x1b[92m
COLOR_LIGHT_YELLOW				= \x1b[93m
COLOR_LIGHT_MAGENTA				= \x1b[95m
COLOR_WHITE						= \x1b[97m

UPDATE_SOURCE_EXT				= c
UPDATE_HEADER_EXT				= h
UPDATE_GO_DEEPER				= false

TARGET							= minishell
NAME							= $(TARGET)

SOURCES							= ./argument_builder.c ./argument_builder_debugger.c ./arraylist_add.c ./arraylist_add_all.c ./arraylist_clear.c ./arraylist_create.c ./arraylist_destroy.c ./arraylist_duplicate.c ./arraylist_get.c ./arraylist_grow.c ./arraylist_index_of.c ./arraylist_init.c ./arraylist_remove.c ./arraylist_remove_at.c ./arraylist_sort.c ./buildin_matcher.c ./builtin.c ./builtin_error.c ./builtin_handler_cd.c ./builtin_handler_echo.c ./builtin_handler_env.c ./builtin_handler_exit.c ./builtin_handler_export.c ./builtin_handler_pwd.c ./builtin_handler_unset.c ./env_append.c ./env_array.c ./env_compare.c ./env_dump.c ./env_finalize.c ./env_get.c ./env_initializer.c ./env_loader.c ./env_set.c ./env_unset.c ./env_var_creator.c ./env_var_free.c ./env_var_validity.c ./evaluator_env_var.c ./evaluator_next.c ./evaluator_quote_double.c ./evaluator_quote_single.c ./evaluator_tilde.c ./evaluator_token.c ./evaluator_utilities.c ./executor_builder.c ./home_cache.c ./home_get.c ./main.c ./minishell_error.c ./minishell_evaluator.c ./minishell_evaluator_builtin.c ./minishell_exit.c ./minishell_initialize.c ./minishell_input.c ./minishell_pre_loop.c ./minishell_process_kill.c ./minishell_prompt.c ./minishell_signals.c ./process_debugger.c ./process_destroy.c ./process_execute.c ./process_file_finder.c ./signal_handler_interrupt.c ./signal_handler_quit.c ./token.c ./token_arg_group.c ./token_io_file.c
HEADERS							= ./arraylist.h ./minishell.h

LIBRARIES						= ft_printf libft
LIBRARIES_FILES					:= $(foreach lib,$(LIBRARIES),$(wildcard $(lib)/*.a))

OBJECTS							= $(SOURCES:.c=.o)

FLAGS							= -Wall -Wextra -Werror -g3 -O0
FLAGS_NAME						= -o
TARGET_REQUIRED_FLAGS			= 
COMPILER						= gcc

FLAGS_FINAL						= $(FLAGS)
FLAGS_NAME_FINAL				= $(FLAGS_NAME)
TARGET_REQUIRED_FLAGS_FINAL		= $(TARGET_REQUIRED_FLAGS)
COMPILER_FINAL					= $(COMPILER)

MAKE_PREFIX						= "$(COLOR_LIGHT_MAGENTA)[$(COLOR_LIGHT_GREEN) make: $(TARGET) $(COLOR_LIGHT_MAGENTA)]"

.c.o:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling: $(COLOR_LIGHT_YELLOW)$<$(COLOR_RESET)"
	@${COMPILER} ${FLAGS} $(TARGET_REQUIRED_FLAGS) $(FLAGS_NAME) ${<:.c=.o} -c $<

$(NAME): $(OBJECTS) gather.py
	@if [ "$(LIBRARIES)" != "" ]; then make $(LIBRARIES); fi;
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling target: $(COLOR_LIGHT_YELLOW)$(TARGET)$(COLOR_RESET)"
	@${COMPILER_FINAL} ${FLAGS_FINAL} $(TARGET_REQUIRED_FLAGS_FINAL) $(FLAGS_NAME_FINAL) $(NAME) $$(python3 gather.py . a true) $(OBJECTS)

all: $(NAME)

fclean: clean
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Removed target$(COLOR_RESET)"
	@rm -f $(NAME)

clean:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Removed objects$(COLOR_RESET)"
	@rm -f $(OBJECTS)
	@rm -f gather.py updater.py find_libs.py

re: fclean all

$(LIBRARIES):
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling library: $(COLOR_LIGHT_YELLOW)$@$(COLOR_RESET)"
	@make -C $@

norm:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Calling the norminette...$(COLOR_RESET)"
	@norminette $(SOURCES) $(HEADERS)

gather.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQoNCg0KZGVmIGV4cGxvcmUocGF0aCwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyPUZhbHNlKToNCiAgICBmaWxlcyA9IFtdDQogICAgDQogICAgZm9yIGZpbGUgaW4gb3MubGlzdGRpcihwYXRoKToNCiAgICAgICAgZmlsZSA9IG9zLnBhdGguam9pbihwYXRoLCBmaWxlKQ0KICAgICAgICANCiAgICAgICAgaWYgb3MucGF0aC5pc2ZpbGUoZmlsZSk6DQogICAgICAgICAgICBpZiBsZW4oZXh0ZW5zaW9ucykgIT0gMCBhbmQgb3MucGF0aC5zcGxpdGV4dChmaWxlKVsxXVsxOl0gbm90IGluIGV4dGVuc2lvbnM6DQogICAgICAgICAgICAgICAgY29udGludWUNCiAgICAgICAgICAgIA0KICAgICAgICAgICAgZmlsZXMuYXBwZW5kKGZpbGUpDQogICAgICAgIGVsc2U6DQogICAgICAgICAgICBpZiBnb19kZWVwZXI6DQogICAgICAgICAgICAgICAgZmlsZXMuZXh0ZW5kKGV4cGxvcmUoZmlsZSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKSkNCiAgICANCiAgICByZXR1cm4gZmlsZXMNCg0KDQphcmd2ID0gc3lzLmFyZ3YNCmFyZ2MgPSBsZW4oYXJndikNCg0KaWYgYXJnYyA8IDI6DQogICAgcHJpbnQoInVzYWdlOiB7fSBwYXRoIFsgZXh0ZW5zaW9ucyAuLi4gXSBbIGdvX2RlZXBlciAoYm9vbCkgXSIuZm9ybWF0KGFyZ3ZbMF0pKQ0KICAgIGV4aXQoMSkNCg0KZXh0ZW5zaW9ucyA9IFsgZXh0ZW5zaW9uLnJlcGxhY2UoIi4iLCAiIikgZm9yIGV4dGVuc2lvbiBpbiBhcmd2WzI6XSBdDQpnb19kZWVwZXIgPSBUcnVlDQoNCmlmIGxlbihleHRlbnNpb25zKSAhPSAwOg0KICAgIGxhc3QgPSBleHRlbnNpb25zW2xlbihleHRlbnNpb25zKSAtIDE6XVswXQ0KICAgIA0KICAgIGlmIGxhc3QgaW4gWyAiMCIsICIxIiwgInRydWUiLCAiZmFsc2UiIF06DQogICAgICAgIGdvX2RlZXBlciA9IGxhc3QgaW4gWyAiMSIsICJ0cnVlIiBdDQogICAgICAgIGV4dGVuc2lvbnMgPSBleHRlbnNpb25zWzpsZW4oZXh0ZW5zaW9ucykgLSAxXQ0KDQpmaWxlcyA9IGV4cGxvcmUoYXJndlsxXSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKQ0KDQpwcmludCgiICIuam9pbihmaWxlcykpDQo=" | base64 -D > gather.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created gather.py file.$(COLOR_RESET)"

find_libs.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQoNCmFyZ3YgPSBzeXMuYXJndg0KYXJnYyA9IGxlbihhcmd2KQ0KDQppZiBhcmdjIDwgMjoNCiAgICBwcmludCgidXNhZ2U6IHt9IHBhdGgiLmZvcm1hdChhcmd2WzBdKSkNCiAgICBleGl0KDEpDQogICAgDQpsaWJyYXJpZXMgPSBbXQ0KDQpmb3IgcGF0aCBpbiBvcy5saXN0ZGlyKGFyZ3ZbMV0pOg0KICAgIGlmIG9zLnBhdGguaXNkaXIocGF0aCk6DQogICAgICAgIGlmICdNYWtlZmlsZScgaW4gb3MubGlzdGRpcihwYXRoKToNCiAgICAgICAgICAgIGxpYnJhcmllcy5hcHBlbmQocGF0aCkNCg0KcHJpbnQoIiAiLmpvaW4obGlicmFyaWVzKSkNCg==" | base64 -D > find_libs.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created find_libs.py file.$(COLOR_RESET)"

updater.py:
	@echo "aW1wb3J0IG9zCmltcG9ydCByZQppbXBvcnQgc3lzCgphcmd2ID0gc3lzLmFyZ3YKYXJnYyA9IGxlbihhcmd2KQoKaWYgYXJnYyA8IDI6CiAgICBwcmludCgidXNhZ2U6IHt9IGtleSA8IHZhbHVlIi5mb3JtYXQoYXJndlswXSkpCiAgICBleGl0KDEpCgprZXkgPSBhcmd2WzFdCnZhbHVlID0gc3lzLnN0ZGluLnJlYWQoKS5yZXBsYWNlKCJcbiIsICIiKQoKd2l0aCBvcGVuKCJNYWtlZmlsZSIsICJyIikgYXMgZmlsZToKICAgIGNvbnRlbnQgPSBmaWxlLnJlYWQoKQogICAgCmxpbmVzID0gW10KCmZvciBsaW5lIGluIGNvbnRlbnQuc3BsaXQoJ1xuJyk6CiAgICBtYXRjaGVzID0gcmUuZmluZGl0ZXIociIiICsga2V5ICsgIihbXHRdKykuKiQiLCBsaW5lLCByZS5NVUxUSUxJTkUpCiAgICAKICAgIGZvdW5kID0gRmFsc2UKICAgIAogICAgZm9yIG1hdGNoIGluIG1hdGNoZXM6CiAgICAgICAgZm91bmQgPSBUcnVlCiAgICAgICAgCiAgICAgICAgbGluZXMuYXBwZW5kKCJ7fXt9PSB7fSIuZm9ybWF0KGtleSwgbWF0Y2guZ3JvdXAoMSksIHZhbHVlKSkKICAgICAgICAKICAgICAgICBicmVhawoKICAgIGlmIG5vdCBmb3VuZDoKICAgICAgICBsaW5lcy5hcHBlbmQobGluZSkKCndpdGggb3BlbigiTWFrZWZpbGUiLCAidyIpIGFzIGZpbGU6CiAgICBmaWxlLndyaXRlKCJcbiIuam9pbihsaW5lcykp" | base64 -D > updater.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created updater.py file.$(COLOR_RESET)"

update: gather.py find_libs.py updater.py
	@echo $$(python3 gather.py . $(UPDATE_SOURCE_EXT) $(UPDATE_GO_DEEPER)) | python3 updater.py SOURCES
	@echo $$(python3 gather.py . $(UPDATE_HEADER_EXT) $(UPDATE_GO_DEEPER)) | python3 updater.py HEADERS
	@echo $$(python3 find_libs.py .) | python3 updater.py LIBRARIES
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Makefile is now up-to-date.$(COLOR_RESET)"

.PHONY: all clean fclean re .c.o norm update $(LIBRARIES)