NAME = ex04
CC = c++ 
CCFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp

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
