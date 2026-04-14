NAME = ex03
CC = c++ 
CCFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp\
	  HumanA.cpp\
	  HumanB.cpp\
	  Weapon.cpp\

OBJS = $(SRC:.cpp=.o)
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CCFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
