NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = execution.c\
	  free.c\
	  here_doc.c\
	  init_pipex.c\
	  main.c\
	  path.c\
	  pipeline.c\
	  secure.c\
	  process.c\

OBJS = $(SRC:.c=.o)

LIB_DIR = lib
LIB_A = $(LIB_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -sC $(LIB_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_A) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIB_DIR) fclean

re: fclean all


.PHONY: all clean fclean re rec