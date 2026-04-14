NAME = so_long
NAME_BONUS = so_long_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g 
MLX_FLAGS =  -lX11 -lXext -lm

SRC = src/main.c\
	  src/close_game.c\
	  src/free.c\
	  src/exit_checker.c\
	  src/render_map.c\
	  src/init_map.c \
	  src/init_game.c \
	  src/inputs.c \
	  src/verify.c \

SRC_BONUS = src_bonus/close_game.c\
			src_bonus/exit_checker.c\
			src_bonus/free.c\
			src_bonus/init_game.c\
			src_bonus/init_map.c\
			src_bonus/inputs.c\
			src_bonus/main.c\
			src_bonus/render_map.c\
			src_bonus/verify.c\

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)

LIB_DIR = lib
LIB_A = $(LIB_DIR)/libft.a

MLX_DIR = MLX
MLX_A = $(MLX_DIR)/libmlx.a

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	@$(MAKE) -sC $(LIB_DIR)
	@$(MAKE) -sC $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_A) $(MLX_A) -o $(NAME) $(MLX_FLAGS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(MAKE) -sC $(LIB_DIR)
	@$(MAKE) -sC $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIB_A) $(MLX_A) -o $(NAME_BONUS) $(MLX_FLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -sC $(LIB_DIR) fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus