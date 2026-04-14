NAME = ex02
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = Base.cpp\
	   main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(CPP)

fclean: clean

	@rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re