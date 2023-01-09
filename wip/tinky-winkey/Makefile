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

SVC_NAME = svc.exe
SVC_SOURCES= \
  svc\cli.cpp \
  svc\service.cpp
SVC_OBJECTS=$(SVC_SOURCES:.cpp=.obj)

WINKEY_NAME = winkey.exe
WINKEY_SOURCES= \
  winkey\keylogger.cpp \
  winkey\utf8.cpp \
  winkey\winkey.cpp
WINKEY_OBJECTS=$(WINKEY_SOURCES:.cpp=.obj)

all: $(SVC_NAME) $(WINKEY_NAME)

.cpp.obj:
	cl /c /nologo /EHsc /Wall /WX /Fo$@ /Tp$<

$(SVC_NAME): $(SVC_OBJECTS)
	link /nologo /out:$(SVC_NAME) $(SVC_OBJECTS)

$(WINKEY_NAME): $(WINKEY_OBJECTS)
	link /nologo /out:$(WINKEY_NAME) $(WINKEY_OBJECTS)

clean:
	del $(SVC_OBJECTS) $(WINKEY_OBJECTS)

fclean: clean
	del $(SVC_NAME) $(WINKEY_NAME)

re: fclean all

.PHONY: all clean fclean re .cpp.obj
