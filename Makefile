##
## Makefile for Zappy in /home/lecler_i/Work/Epitech/Tek2/SysUnix/PSU_2013_zappy
##
## Made by Thomas LECLERCQ
## Login   <lecler_i@epitech.net>
##
## Started on  Fri Jun 20 10:16:06 2014 Thomas LECLERCQ
## Last update Wed Jul  2 23:01:06 2014 Thomas LECLERCQ
##

NAME =		test

SOURCE_DIR =	source

INCLUDE_DIR =	include

BUILD_DIR =	build

FILES +=	network.c \
		socket.c \
		send.c \
		clients.c \
		buffer/circular_buffer.c \

OBJ_FILES =	$(addprefix $(BUILD_DIR)/, $(FILES:.c=.o))

CXX =		gcc

RM =		rm -f

CXXFLAGS =	-I$(INCLUDE_DIR) -I$(SOURCE_DIR) -Wextra -Wall -Wno-long-long -Wno-unused-parameter

LDFLAGS =

-include $(OBJ_FILES:.o=.d)

$(NAME):	$(OBJ_FILES)
		$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o:$(SOURCE_DIR)/%.c
		@ mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) -g3 -c -o $@ $<

all:		$(NAME)

clean:
		$(RM) $(OBJ_FILES) $(OBJ_FILES:.o=.d)

fclean: 	clean
		$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY: 	all clean fclean re
