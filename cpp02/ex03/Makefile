NAME = BSP
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = Fixed.cpp\
	  main.cpp\
	  bsp.cpp\
	  Point.cpp\

OBJ = $(SRC:.cpp=.o)

all: $(NAME)
	@echo "\033[35mCompilation done\033[0m"

$(NAME): $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@

clean: 
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@echo "\033[35mCleaning accomplished\033[0m"

re: fclean all

.PHONY: all clean fclean re