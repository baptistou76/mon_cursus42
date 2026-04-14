NAME = PhoneBook
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g
SRCS = Contact.cpp\
	   PhoneBook.cpp\

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