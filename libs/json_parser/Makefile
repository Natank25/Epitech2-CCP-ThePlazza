##
## EPITECH PROJECT, 2026
## my_teams
## File description:
## Makefile
##

SRC = $(addprefix src/, \
		Json.cpp		\
		JsonCore.cpp	\
		JsonString.cpp	\
		JsonNumber.cpp	\
		JsonArray.cpp	\
		JsonObject.cpp	\
	)

NAME = libjson_parser.a

OBJ = $(SRC:.cpp=.o)

CXX = clang++
AR = ar

CXXFLAGS += --std=c++20 -Wall -Wextra -Werror -g3

all: $(NAME) include/Json.hpp

$(NAME): $(OBJ)
	$(AR) rc $@ $(OBJ)
	@ranlib $@

Json.hpp:
	cp src/Json.hpp .

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

