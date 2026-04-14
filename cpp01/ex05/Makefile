NAME = ex05
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = Harl.cpp\
      main.cpp\

OBJS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CPP) $(CCFLAGS) $(OBJS) -o $(NAME)

clean: 
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re