NAME = ex02
CPP = c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98
SRC = ClapTrap.cpp\
	  main.cpp\
	  ScavTrap.cpp\
	  FragTrap.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re