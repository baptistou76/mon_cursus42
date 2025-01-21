NAME = push_swap

CFLAGS = -Wall -Wextra -Werror 

SRC = parsing_digits.c\
	  pop.c\
	  push.c\
	  create_node.c\
	  ft_split.c\
	  main.c\
	  rotate_a.c\
	  rotate_b.c\
	  swapandpush.c\
	  utils.c\
	  

OBJ = $(SRC:.c=.o)

ARFLAGS = rcs

LIB_DIR = libft
LIBFT = $(LIB_DIR)/libft.a

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) lib
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

lib:
	$(MAKE) -C $(LIB_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean 
	
re: fclean all

.PHONY: all clean fclean re bonus