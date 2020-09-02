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

COLOR_RESET				= \033[0m
COLOR_LIGHT_GREEN		= \033[92m
COLOR_LIGHT_YELLOW		= \033[93m
COLOR_LIGHT_MAGENTA		= \033[95m
COLOR_WHITE				= \033[97m

FIX_SOURCE_EXT			= c
FIX_HEADER_EXT			= h
FIX_GO_DEEPER			= false

MAKE_PREFIX				= "$(COLOR_LIGHT_MAGENTA)[$(COLOR_LIGHT_GREEN) make $(COLOR_LIGHT_MAGENTA)]"

TARGET					= philo_one
SOURCES					= ./errors.c ./ft_atoi.c ./ft_malloc.c ./ft_memset.c ./ft_putstr.c ./ft_sputnbr.c ./ft_sputstr.c ./ft_strlen.c ./main.c ./ph_main.c ./ph_millis.c ./ph_runnable.c ./ph_sim_start.c ./ph_sleep.c ./ph_table.c ./ph_update.c ./phm.c ./phm_dead.c ./phm_join.c ./phm_run_starvation.c ./phm_threads.c
HEADERS					= ./philosophers.h ./philosophers_structs.h
OBJECTS					= $(SOURCES:.c=.o)
FLAGS					= -Wall -Wextra -Werror -g3 -O0 # -fsanitize=address
TARGET_REQUIRED_FLAGS	= -pthread
COMPILER				= gcc

.c.o:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling: $(COLOR_LIGHT_YELLOW)$<$(COLOR_RESET)"
	@${COMPILER} ${FLAGS} $(TARGET_REQUIRED_FLAGS) -c $< -o ${<:.c=.o}

$(TARGET): ${OBJECTS}
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling target: $(COLOR_LIGHT_YELLOW)$(TARGET)$(COLOR_RESET)"
	@${COMPILER} ${FLAGS} $(TARGET_REQUIRED_FLAGS) $(OBJECTS) -o $(TARGET)

all: $(TARGET)
    
fclean: clean
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Removed target$(COLOR_RESET)"
	@rm -f $(TARGET)
    
clean:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Removed objects$(COLOR_RESET)"
	@rm -f $(OBJECTS)
	@rm -f gather.py updater.py
    
re: fclean all

norm:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Calling the norminette...$(COLOR_RESET)"
	@norminette $(SOURCES) $(HEADERS)
	
gather.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQoNCg0KZGVmIGV4cGxvcmUocGF0aCwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyPUZhbHNlKToNCiAgICBmaWxlcyA9IFtdDQogICAgDQogICAgZm9yIGZpbGUgaW4gb3MubGlzdGRpcihwYXRoKToNCiAgICAgICAgZmlsZSA9IG9zLnBhdGguam9pbihwYXRoLCBmaWxlKQ0KICAgICAgICANCiAgICAgICAgaWYgb3MucGF0aC5pc2ZpbGUoZmlsZSk6DQogICAgICAgICAgICBpZiBsZW4oZXh0ZW5zaW9ucykgIT0gMCBhbmQgb3MucGF0aC5zcGxpdGV4dChmaWxlKVsxXVsxOl0gbm90IGluIGV4dGVuc2lvbnM6DQogICAgICAgICAgICAgICAgY29udGludWUNCiAgICAgICAgICAgIA0KICAgICAgICAgICAgZmlsZXMuYXBwZW5kKGZpbGUpDQogICAgICAgIGVsc2U6DQogICAgICAgICAgICBpZiBnb19kZWVwZXI6DQogICAgICAgICAgICAgICAgZmlsZXMuZXh0ZW5kKGV4cGxvcmUoZmlsZSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKSkNCiAgICANCiAgICByZXR1cm4gZmlsZXMNCg0KDQphcmd2ID0gc3lzLmFyZ3YNCmFyZ2MgPSBsZW4oYXJndikNCg0KaWYgYXJnYyA8IDI6DQogICAgcHJpbnQoInVzYWdlOiB7fSBwYXRoIFsgZXh0ZW5zaW9ucyAuLi4gXSBbIGdvX2RlZXBlciAoYm9vbCkgXSIuZm9ybWF0KGFyZ3ZbMF0pKQ0KICAgIGV4aXQoMSkNCg0KZXh0ZW5zaW9ucyA9IFsgZXh0ZW5zaW9uLnJlcGxhY2UoIi4iLCAiIikgZm9yIGV4dGVuc2lvbiBpbiBhcmd2WzI6XSBdDQpnb19kZWVwZXIgPSBUcnVlDQoNCmlmIGxlbihleHRlbnNpb25zKSAhPSAwOg0KICAgIGxhc3QgPSBleHRlbnNpb25zW2xlbihleHRlbnNpb25zKSAtIDE6XVswXQ0KICAgIA0KICAgIGlmIGxhc3QgaW4gWyAiMCIsICIxIiwgInRydWUiLCAiZmFsc2UiIF06DQogICAgICAgIGdvX2RlZXBlciA9IGxhc3QgaW4gWyAiMSIsICJ0cnVlIiBdDQogICAgICAgIGV4dGVuc2lvbnMgPSBleHRlbnNpb25zWzpsZW4oZXh0ZW5zaW9ucykgLSAxXQ0KDQpmaWxlcyA9IGV4cGxvcmUoYXJndlsxXSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKQ0KDQpwcmludCgiICIuam9pbihmaWxlcykpDQo=" | base64 -D > gather.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created gather.py file.$(COLOR_RESET)"
	
updater.py:
	@echo "aW1wb3J0IG9zCmltcG9ydCByZQppbXBvcnQgc3lzCgphcmd2ID0gc3lzLmFyZ3YKYXJnYyA9IGxlbihhcmd2KQoKaWYgYXJnYyA8IDI6CiAgICBwcmludCgidXNhZ2U6IHt9IGtleSA8IHZhbHVlIi5mb3JtYXQoYXJndlswXSkpCiAgICBleGl0KDEpCgprZXkgPSBhcmd2WzFdCnZhbHVlID0gc3lzLnN0ZGluLnJlYWQoKS5yZXBsYWNlKCJcbiIsICIiKQoKd2l0aCBvcGVuKCJNYWtlZmlsZSIsICJyIikgYXMgZmlsZToKICAgIGNvbnRlbnQgPSBmaWxlLnJlYWQoKQogICAgCmxpbmVzID0gW10KCmZvciBsaW5lIGluIGNvbnRlbnQuc3BsaXQoJ1xuJyk6CiAgICBtYXRjaGVzID0gcmUuZmluZGl0ZXIociIiICsga2V5ICsgIihbXHRdKykuKiQiLCBsaW5lLCByZS5NVUxUSUxJTkUpCiAgICAKICAgIGZvdW5kID0gRmFsc2UKICAgIAogICAgZm9yIG1hdGNoIGluIG1hdGNoZXM6CiAgICAgICAgZm91bmQgPSBUcnVlCiAgICAgICAgCiAgICAgICAgbGluZXMuYXBwZW5kKCJ7fXt9PSB7fSIuZm9ybWF0KGtleSwgbWF0Y2guZ3JvdXAoMSksIHZhbHVlKSkKICAgICAgICAKICAgICAgICBicmVhawoKICAgIGlmIG5vdCBmb3VuZDoKICAgICAgICBsaW5lcy5hcHBlbmQobGluZSkKCndpdGggb3BlbigiTWFrZWZpbGUiLCAidyIpIGFzIGZpbGU6CiAgICBmaWxlLndyaXRlKCJcbiIuam9pbihsaW5lcykp" | base64 -D > updater.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created updater.py file.$(COLOR_RESET)"

update: gather.py updater.py
	@echo $$(python3 gather.py . $(FIX_SOURCE_EXT) $(FIX_GO_DEEPER)) | python3 updater.py SOURCES
	@echo $$(python3 gather.py . $(FIX_HEADER_EXT) $(FIX_GO_DEEPER)) | python3 updater.py HEADERS
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Makefile is now up-to-date.$(COLOR_RESET)"

.PHONY: all clean fclean re .c.o norm update
