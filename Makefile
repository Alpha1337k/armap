NAME=armap

CC=clang++
FLAGS=-Wall -Werror -Wextra -O3
DEBUG_FLAGS=-g -fsanitize=address
SRC=test.cpp
LIBS=
OBJ=
RM =rm -rf

all: $(NAME)

$(NAME): $(SRC) Armap.hpp
	$(CC) -D MINE $(FLAGS) $(LIBS) $(SRC) -o $(NAME)

real:
	$(CC) $(FLAGS) $(LIBS) $(SRC) -o $(NAME)_real

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./$(NAME)

debug: fclean
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(LIBS) $(SRC) -o $(NAME)
