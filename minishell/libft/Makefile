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

TARGET							= libft
NAME							= $(TARGET).a

SOURCES							= ./ft_abs.c ./ft_atoi.c ./ft_atoi_base.c ./ft_atoi_base_insensitive.c ./ft_base_resolve.c ./ft_base_validate.c ./ft_bzero.c ./ft_calloc.c ./ft_chrmult.c ./ft_chrtostr.c ./ft_emptystr.c ./ft_fake_use.c ./ft_free_and_release.c ./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c ./ft_isdigit.c ./ft_ishex.c ./ft_isinstr.c ./ft_islower.c ./ft_isoctal.c ./ft_isprint.c ./ft_isquote.c ./ft_isupper.c ./ft_iswspace.c ./ft_itoa.c ./ft_itoa_base.c ./ft_itoa_u_base.c ./ft_lsr.c ./ft_lstadd_back.c ./ft_lstadd_front.c ./ft_lstclear.c ./ft_lstdelone.c ./ft_lstiter.c ./ft_lstlast.c ./ft_lstmap.c ./ft_lstnew.c ./ft_lstsize.c ./ft_max.c ./ft_memccpy.c ./ft_memchr.c ./ft_memcmp.c ./ft_memcpy.c ./ft_memjoin.c ./ft_memmove.c ./ft_memset.c ./ft_min.c ./ft_putchar_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c ./ft_putstr_fd.c ./ft_putuchar_fd.c ./ft_sort_comp.c ./ft_split.c ./ft_split_free.c ./ft_split_length.c ./ft_str_isdigit.c ./ft_strchr.c ./ft_strcmp.c ./ft_strcontain.c ./ft_strdup.c ./ft_strjoin.c ./ft_strjoin3.c ./ft_strjoin_free.c ./ft_strjoin_sided.c ./ft_strlcat.c ./ft_strlcpy.c ./ft_strlen.c ./ft_strmapi.c ./ft_strncmp.c ./ft_strnstr.c ./ft_strrchr.c ./ft_strtrim.c ./ft_substr.c ./ft_swap.c ./ft_swap_double.c ./ft_swap_int.c ./ft_tolower.c ./ft_toupper.c ./ft_zero_if_neg.c ./get_next_line.c
HEADERS							= ./get_next_line.h ./libft.h

LIBRARIES						= 
LIBRARIES_FILES					:= $(foreach lib,$(LIBRARIES),$(wildcard $(lib)/*.a))

OBJECTS							= $(SOURCES:.c=.o)

FLAGS							= -Wall -Wextra -Werror -g3 -O3
FLAGS_NAME						= -o
TARGET_REQUIRED_FLAGS			= 
COMPILER						= gcc

FLAGS_FINAL						= -rcs
FLAGS_NAME_FINAL				= 
TARGET_REQUIRED_FLAGS_FINAL		= 
COMPILER_FINAL					= ar

MAKE_PREFIX						= "$(COLOR_LIGHT_MAGENTA)[$(COLOR_LIGHT_GREEN) make: $(TARGET) $(COLOR_LIGHT_MAGENTA)]"

.c.o:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling: $(COLOR_LIGHT_YELLOW)$<$(COLOR_RESET)"
	@${COMPILER} ${FLAGS} $(TARGET_REQUIRED_FLAGS) $(FLAGS_NAME) ${<:.c=.o} -c $<

$(NAME): $(OBJECTS)
	@if [ "$(LIBRARIES)" != "" ]; then make $(LIBRARIES); fi;
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling target: $(COLOR_LIGHT_YELLOW)$(TARGET)$(COLOR_RESET)"
	@${COMPILER_FINAL} ${FLAGS_FINAL} $(TARGET_REQUIRED_FLAGS_FINAL) $(FLAGS_NAME_FINAL) $(NAME) $(LIBRARIES_FILES) $(OBJECTS)

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
	@#echo $$(python3 find_libs.py .) | python3 updater.py LIBRARIES
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Makefile is now up-to-date.$(COLOR_RESET)"

.PHONY: all clean fclean re .c.o norm update $(LIBRARIES)