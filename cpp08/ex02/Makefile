NAME = ex02
ADD_NAME = ex02_add
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp

SRCS_ADD = main2.cpp

OBJS = $(SRCS:.cpp=.o)
OBJS_ADD = $(SRCS_ADD:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

add: $(OBJS_ADD)
	@$(CPP) $(CPPFLAGS) $(OBJS_ADD) -o $(ADD_NAME)

clean:
	@rm -f $(OBJS) $(OBJS_ADD)

fclean: clean
	@rm -f $(NAME) $(ADD_NAME)

re: fclean all

.PHONY: all clean fclean re add