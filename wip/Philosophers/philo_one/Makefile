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

COLOR_RESET				= \e[0m
COLOR_LIGHT_GREEN		= \e[92m
COLOR_LIGHT_YELLOW		= \e[93m
COLOR_LIGHT_MAGENTA		= \e[95m
COLOR_WHITE				= \e[97m

FIX_SOURCE_EXT			= c
FIX_HEADER_EXT			= h
FIX_GO_DEEPER			= false

MAKE_PREFIX				= "$(COLOR_LIGHT_MAGENTA)[$(COLOR_LIGHT_GREEN) make $(COLOR_LIGHT_MAGENTA)]"

TARGET					= philo_one
SOURCES					= ./errors.c ./fork_create.c ./fork_destroy.c ./fork_grab.c ./fork_release.c ./main.c ./philosophers.c ./philosophers_create.c ./philosophers_debugger.c ./philosophers_destroy.c ./philosophers_monitor.c ./philosophers_ring_attach_param.c ./philosophers_ring_create.c ./philosophers_ring_destroy.c ./philosophers_ring_end.c ./philosophers_ring_forks.c ./philosophers_ring_start.c ./philosophers_ring_threader.c ./philosophers_ring_wait.c ./philosophers_routine.c ./philosophers_status.c ./x_atoi.c ./x_memset.c ./x_millis.c ./x_putnbr.c ./x_putstr.c ./x_strlen.c
HEADERS					= ./philosophers.h
OBJECTS					= $(SOURCES:.c=.o)
FLAGS					= -Wall -Wextra -Werror -g3 -O0
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
    
re: fclean all

norm:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Calling the norminette...$(COLOR_RESET)"
	@norminette $(SOURCES) $(HEADERS)
	
gather.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQoNCg0KZGVmIGV4cGxvcmUocGF0aCwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyPUZhbHNlKToNCiAgICBmaWxlcyA9IFtdDQogICAgDQogICAgZm9yIGZpbGUgaW4gb3MubGlzdGRpcihwYXRoKToNCiAgICAgICAgZmlsZSA9IG9zLnBhdGguam9pbihwYXRoLCBmaWxlKQ0KICAgICAgICANCiAgICAgICAgaWYgb3MucGF0aC5pc2ZpbGUoZmlsZSk6DQogICAgICAgICAgICBpZiBsZW4oZXh0ZW5zaW9ucykgIT0gMCBhbmQgb3MucGF0aC5zcGxpdGV4dChmaWxlKVsxXVsxOl0gbm90IGluIGV4dGVuc2lvbnM6DQogICAgICAgICAgICAgICAgY29udGludWUNCiAgICAgICAgICAgIA0KICAgICAgICAgICAgZmlsZXMuYXBwZW5kKGZpbGUpDQogICAgICAgIGVsc2U6DQogICAgICAgICAgICBpZiBnb19kZWVwZXI6DQogICAgICAgICAgICAgICAgZmlsZXMuZXh0ZW5kKGV4cGxvcmUoZmlsZSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKSkNCiAgICANCiAgICByZXR1cm4gZmlsZXMNCg0KDQphcmd2ID0gc3lzLmFyZ3YNCmFyZ2MgPSBsZW4oYXJndikNCg0KaWYgYXJnYyA8IDI6DQogICAgcHJpbnQoInVzYWdlOiB7fSBwYXRoIFsgZXh0ZW5zaW9ucyAuLi4gXSBbIGdvX2RlZXBlciAoYm9vbCkgXSIuZm9ybWF0KGFyZ3ZbMF0pKQ0KICAgIGV4aXQoMSkNCg0KZXh0ZW5zaW9ucyA9IFsgZXh0ZW5zaW9uLnJlcGxhY2UoIi4iLCAiIikgZm9yIGV4dGVuc2lvbiBpbiBhcmd2WzI6XSBdDQpnb19kZWVwZXIgPSBUcnVlDQoNCmlmIGxlbihleHRlbnNpb25zKSAhPSAwOg0KICAgIGxhc3QgPSBleHRlbnNpb25zW2xlbihleHRlbnNpb25zKSAtIDE6XVswXQ0KICAgIA0KICAgIGlmIGxhc3QgaW4gWyAiMCIsICIxIiwgInRydWUiLCAiZmFsc2UiIF06DQogICAgICAgIGdvX2RlZXBlciA9IGxhc3QgaW4gWyAiMSIsICJ0cnVlIiBdDQogICAgICAgIGV4dGVuc2lvbnMgPSBleHRlbnNpb25zWzpsZW4oZXh0ZW5zaW9ucykgLSAxXQ0KDQpmaWxlcyA9IGV4cGxvcmUoYXJndlsxXSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKQ0KDQpwcmludCgiICIuam9pbihmaWxlcykpDQo=" | base64 -d > gather.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created gather.py file.$(COLOR_RESET)"

update: gather.py
	@sed -i 's/SOURCES[\t][\t]= .*$$/SOURCES\t\t= '"$$(echo $$(python3 gather.py . $(FIX_SOURCE_EXT) $(FIX_GO_DEEPER)) | sed -e 's/\//\\\//g' | sed -e 's/\./\\\./g' | sed -e 's/ /\\ /g')"'/g' Makefile
	@sed -i 's/HEADERS[\t][\t]= .*$$/HEADERS\t\t= '"$$(echo $$(python3 gather.py . $(FIX_HEADER_EXT) $(FIX_GO_DEEPER)) | sed -e 's/\//\\\//g' | sed -e 's/\./\\\./g' | sed -e 's/ /\\ /g')"'/g' Makefile
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Makefile is now up-to-date.$(COLOR_RESET)"

.PHONY: all clean fclean re .c.o norm update