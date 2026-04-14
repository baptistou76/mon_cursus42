NAME = ex03
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = AMateria.cpp\
	   Character.cpp\
	   Cure.cpp\
	   Ice.cpp\
	   MateriaSource.cpp\
	   main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean: 
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
