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

COLOR_RESET				= \033[0m
COLOR_LIGHT_GREEN		= \033[92m
COLOR_LIGHT_YELLOW		= \033[93m
COLOR_LIGHT_MAGENTA		= \033[95m
COLOR_WHITE				= \033[97m

FIX_SOURCE_EXT			= c
FIX_HEADER_EXT			= h
FIX_GO_DEEPER			= false
FIX_SOURCES_DIR			= .
FIX_HEADERS_DIR			= .
FIX_LIBRARIES_DIR		= .

TARGET					= cub3d
SOURCES					= 
HEADERS					= 
LIBRARIES				= 
LIBRARIES_BIN			= 

OBJECTS					= $(SOURCES:.c=.o)

COMPILER				= gcc

FRAMEWORKS				= 
FLAGS					= -Wall -Wextra -Werror -g3 -O0 # -fsanitize=address
TARGET_REQUIRED_FLAGS	= 

TOOL_BASE64_DECODE		= base64 -D

MAKE_PREFIX				= "$(COLOR_LIGHT_MAGENTA)[$(COLOR_LIGHT_GREEN) make: $(TARGET) $(COLOR_LIGHT_MAGENTA)]"

.c.o:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling: $(COLOR_LIGHT_YELLOW)$<$(COLOR_RESET)"
	@${COMPILER} ${FLAGS} $(TARGET_REQUIRED_FLAGS) -c $< -o ${<:.c=.o}

$(TARGET): ${OBJECTS}
	@if [ "$(LIBRARIES)" != "" ]; then make $(LIBRARIES); fi;
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling target: $(COLOR_LIGHT_YELLOW)$(TARGET)$(COLOR_RESET)"
	@${COMPILER} ${FLAGS} $(TARGET_REQUIRED_FLAGS) $(foreach framework,$(FRAMEWORKS),-framework $(framework)) $(LIBRARIES_BIN) $(OBJECTS) -o $(TARGET)

all: $(TARGET)
    
fclean: clean
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Removed target$(COLOR_RESET)"
	@rm -f $(TARGET)
    
clean:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Removed objects$(COLOR_RESET)"
	@rm -f $(OBJECTS)
	@rm -f $(LIBRARIES_BIN)
	@rm -f gather.py updater.py find_libs.py find_libs_bin.py
    
re: fclean all

$(LIBRARIES):
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Compiling library: $(COLOR_LIGHT_YELLOW)$@$(COLOR_RESET)"
	@make -C $@
	@cp -f $$(ls $(foreach bin,$(LIBRARIES_BIN),$@/$(bin)) 2> /dev/null || true) .

norm:
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Calling the norminette...$(COLOR_RESET)"
	@norminette $(SOURCES) $(HEADERS)
	
gather.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQoNCg0KZGVmIGV4cGxvcmUocGF0aCwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyPUZhbHNlKToNCiAgICBmaWxlcyA9IFtdDQogICAgDQogICAgZm9yIGZpbGUgaW4gb3MubGlzdGRpcihwYXRoKToNCiAgICAgICAgZmlsZSA9IG9zLnBhdGguam9pbihwYXRoLCBmaWxlKQ0KICAgICAgICANCiAgICAgICAgaWYgb3MucGF0aC5pc2ZpbGUoZmlsZSk6DQogICAgICAgICAgICBpZiBsZW4oZXh0ZW5zaW9ucykgIT0gMCBhbmQgb3MucGF0aC5zcGxpdGV4dChmaWxlKVsxXVsxOl0gbm90IGluIGV4dGVuc2lvbnM6DQogICAgICAgICAgICAgICAgY29udGludWUNCiAgICAgICAgICAgIA0KICAgICAgICAgICAgZmlsZXMuYXBwZW5kKGZpbGUpDQogICAgICAgIGVsc2U6DQogICAgICAgICAgICBpZiBnb19kZWVwZXI6DQogICAgICAgICAgICAgICAgZmlsZXMuZXh0ZW5kKGV4cGxvcmUoZmlsZSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKSkNCiAgICANCiAgICByZXR1cm4gZmlsZXMNCg0KDQphcmd2ID0gc3lzLmFyZ3YNCmFyZ2MgPSBsZW4oYXJndikNCg0KaWYgYXJnYyA8IDI6DQogICAgcHJpbnQoInVzYWdlOiB7fSBwYXRoIFsgZXh0ZW5zaW9ucyAuLi4gXSBbIGdvX2RlZXBlciAoYm9vbCkgXSIuZm9ybWF0KGFyZ3ZbMF0pKQ0KICAgIGV4aXQoMSkNCg0KZXh0ZW5zaW9ucyA9IFsgZXh0ZW5zaW9uLnJlcGxhY2UoIi4iLCAiIikgZm9yIGV4dGVuc2lvbiBpbiBhcmd2WzI6XSBdDQpnb19kZWVwZXIgPSBUcnVlDQoNCmlmIGxlbihleHRlbnNpb25zKSAhPSAwOg0KICAgIGxhc3QgPSBleHRlbnNpb25zW2xlbihleHRlbnNpb25zKSAtIDE6XVswXQ0KICAgIA0KICAgIGlmIGxhc3QgaW4gWyAiMCIsICIxIiwgInRydWUiLCAiZmFsc2UiIF06DQogICAgICAgIGdvX2RlZXBlciA9IGxhc3QgaW4gWyAiMSIsICJ0cnVlIiBdDQogICAgICAgIGV4dGVuc2lvbnMgPSBleHRlbnNpb25zWzpsZW4oZXh0ZW5zaW9ucykgLSAxXQ0KDQpmaWxlcyA9IGV4cGxvcmUoYXJndlsxXSwgZXh0ZW5zaW9ucywgZ29fZGVlcGVyKQ0KDQpwcmludCgiICIuam9pbihmaWxlcykpDQo=" | $(TOOL_BASE64_DECODE) > gather.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created gather.py file.$(COLOR_RESET)"
	
updater.py:
	@echo "aW1wb3J0IG9zCmltcG9ydCByZQppbXBvcnQgc3lzCgphcmd2ID0gc3lzLmFyZ3YKYXJnYyA9IGxlbihhcmd2KQoKaWYgYXJnYyA8IDI6CiAgICBwcmludCgidXNhZ2U6IHt9IGtleSA8IHZhbHVlIi5mb3JtYXQoYXJndlswXSkpCiAgICBleGl0KDEpCgprZXkgPSBhcmd2WzFdCnZhbHVlID0gc3lzLnN0ZGluLnJlYWQoKS5yZXBsYWNlKCJcbiIsICIiKQoKd2l0aCBvcGVuKCJNYWtlZmlsZSIsICJyIikgYXMgZmlsZToKICAgIGNvbnRlbnQgPSBmaWxlLnJlYWQoKQogICAgCmxpbmVzID0gW10KCmZvciBsaW5lIGluIGNvbnRlbnQuc3BsaXQoJ1xuJyk6CiAgICBtYXRjaGVzID0gcmUuZmluZGl0ZXIociIiICsga2V5ICsgIihbXHRdKykuKiQiLCBsaW5lLCByZS5NVUxUSUxJTkUpCiAgICAKICAgIGZvdW5kID0gRmFsc2UKICAgIAogICAgZm9yIG1hdGNoIGluIG1hdGNoZXM6CiAgICAgICAgZm91bmQgPSBUcnVlCiAgICAgICAgCiAgICAgICAgbGluZXMuYXBwZW5kKCJ7fXt9PSB7fSIuZm9ybWF0KGtleSwgbWF0Y2guZ3JvdXAoMSksIHZhbHVlKSkKICAgICAgICAKICAgICAgICBicmVhawoKICAgIGlmIG5vdCBmb3VuZDoKICAgICAgICBsaW5lcy5hcHBlbmQobGluZSkKCndpdGggb3BlbigiTWFrZWZpbGUiLCAidyIpIGFzIGZpbGU6CiAgICBmaWxlLndyaXRlKCJcbiIuam9pbihsaW5lcykp" | $(TOOL_BASE64_DECODE) > updater.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created updater.py file.$(COLOR_RESET)"

find_libs.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQoNCmFyZ3YgPSBzeXMuYXJndg0KYXJnYyA9IGxlbihhcmd2KQ0KDQppZiBhcmdjIDwgMjoNCiAgICBwcmludCgidXNhZ2U6IHt9IHBhdGgiLmZvcm1hdChhcmd2WzBdKSkNCiAgICBleGl0KDEpDQogICAgDQpsaWJyYXJpZXMgPSBbXQ0KDQpmb3IgcGF0aCBpbiBvcy5saXN0ZGlyKGFyZ3ZbMV0pOg0KICAgIGlmIG9zLnBhdGguaXNkaXIocGF0aCk6DQogICAgICAgIGlmICdNYWtlZmlsZScgaW4gb3MubGlzdGRpcihwYXRoKToNCiAgICAgICAgICAgIGxpYnJhcmllcy5hcHBlbmQocGF0aCkNCg0KcHJpbnQoIiAiLmpvaW4obGlicmFyaWVzKSkNCg==" | $(TOOL_BASE64_DECODE) > find_libs.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created find_libs.py file.$(COLOR_RESET)"

find_libs_bin.py:
	@echo "aW1wb3J0IG9zDQppbXBvcnQgc3lzDQppbXBvcnQgcmUNCg0KYXJndiA9IHN5cy5hcmd2DQphcmdjID0gbGVuKGFyZ3YpDQoNClJFR0VYID0gciIoPzpOQU1FfFRBUkdFVClbIFx0XSo9WyBcdF0qKFtcdy5dKylbXHNdIg0KDQppZiBhcmdjIDwgMjoNCiAgICBwcmludCgidXNhZ2U6IHt9IHBhdGgiLmZvcm1hdChhcmd2WzBdKSkNCiAgICBleGl0KDEpDQogICAgDQpsaWJyYXJpZXMgPSBbXQ0KDQpmb3IgcGF0aCBpbiBvcy5saXN0ZGlyKGFyZ3ZbMV0pOg0KICAgIGlmIG9zLnBhdGguaXNkaXIocGF0aCk6DQogICAgICAgIG1ha2VmaWxlX3BhdGggPSBvcy5wYXRoLmpvaW4ocGF0aCwgIk1ha2VmaWxlIikNCiAgICAgICAgDQogICAgICAgIGlmIG9zLnBhdGguZXhpc3RzKG1ha2VmaWxlX3BhdGgpOg0KICAgICAgICAgICAgd2l0aCBvcGVuKG1ha2VmaWxlX3BhdGgsICJyIikgYXMgZmlsZToNCiAgICAgICAgICAgICAgICBiaW5zID0gW10NCiAgICAgICAgICAgICAgICANCiAgICAgICAgICAgICAgICBmb3IgbWF0Y2ggaW4gcmUuZmluZGl0ZXIoUkVHRVgsIGZpbGUucmVhZCgpLCByZS5NVUxUSUxJTkUpOg0KICAgICAgICAgICAgICAgICAgICBiaW5zLmFwcGVuZChtYXRjaC5ncm91cCgxKSkNCiAgICAgICAgICAgICAgICANCiAgICAgICAgICAgICAgICBpZiBsZW4oYmlucykgPT0gMDoNCiAgICAgICAgICAgICAgICAgICAgcHJpbnQoInt9IHdhcm5pbmc6IG5vIHRhcmdldCBmb3VuZCBmb3IgbGlicmFyeSB7fSIuZm9ybWF0KGFyZ3ZbMF0sIHBhdGgpKQ0KICAgICAgICAgICAgICAgICAgICBjb250aW51ZQ0KICAgICAgICAgICAgICAgIA0KICAgICAgICAgICAgICAgIGlmIGxlbihiaW5zKSA+IDE6DQogICAgICAgICAgICAgICAgICAgIHByaW50KCJ7fSB3YXJuaW5nOiBtb3JlIHRoYW4gb25lIHRhcmdldCBmb3VuZCBmb3IgbGlicmFyeSB7fSAoe30pIi5mb3JtYXQoYXJndlswXSwgcGF0aCwgYmlucykpDQogICAgICAgICAgICAgICAgICAgIA0KICAgICAgICAgICAgICAgIGxpYnJhcmllcy5leHRlbmQoYmlucykNCg0KcHJpbnQoIiAiLmpvaW4obGlicmFyaWVzKSkNCg==" | $(TOOL_BASE64_DECODE) > find_libs_bin.py
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Created find_libs_bin.py file.$(COLOR_RESET)"

update: gather.py updater.py find_libs.py find_libs_bin.py
	@echo $$(python3 gather.py $(FIX_SOURCES_DIR) $(FIX_SOURCE_EXT) $(FIX_GO_DEEPER)) | python3 updater.py SOURCES
	@echo $$(python3 gather.py $(FIX_HEADERS_DIR) $(FIX_HEADER_EXT) $(FIX_GO_DEEPER)) | python3 updater.py HEADERS
	@echo $$(python3 find_libs.py $(FIX_LIBRARIES_DIR)) | python3 updater.py LIBRARIES
	@echo $$(python3 find_libs_bin.py $(FIX_LIBRARIES_DIR)) | python3 updater.py LIBRARIES_BIN
	@echo $(MAKE_PREFIX) "$(COLOR_WHITE)Makefile is now up-to-date.$(COLOR_RESET)"

.PHONY: all clean fclean re .c.o norm update $(LIBRARIES)
