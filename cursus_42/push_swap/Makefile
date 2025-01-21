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
PRINT_DIR = ft_printf
FT_PRINTF = $(PRINT_DIR)/ft_printf.a

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) lib print
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(FT_PRINTF) -o $(NAME)

lib:
	$(MAKE) -C $(LIB_DIR) all

print:
	$(MAKE) -C $(PRINT_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean 
	$(MAKE) -C $(PRINT_DIR) fclean
	
re: fclean all

.PHONY: all clean fclean re bonus