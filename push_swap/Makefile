NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = a_vers_b.c\
	  b_vers_a.c\
	  algo_3.c\
	  algo_turc.c\
	  chercheurs.c\
	  double_liste_chainee.c\
	  erreurs.c\
	  main.c\
	  poussee.c\
	  rotation_inversee.c\
	  rotation.c\
	  swaps.c\
	  utils.c\
	  verifs.c\

OBJS = $(SRC:.c=.o)

LIB_DIR = libft
LIB_A = $(LIB_DIR)/libft.a

PRINT_DIR = ft_printf
PRINT_A = $(PRINT_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIB_DIR) all
	@$(MAKE) -C $(PRINT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_A) $(PRINT_A) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(PRINT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean
	@$(MAKE) -C $(PRINT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re
