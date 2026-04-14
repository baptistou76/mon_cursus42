# ==================== cub3D Makefile ====================
NAME		= cub3D

# Dossiers
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
LIB_DIR		= lib
MLX_DIR		= minilibx-linux

# Libs
LIBFT		= $(LIB_DIR)/libcub.a
MLX_LIB		= $(MLX_DIR)/libmlx.a

# Compilation
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I$(INC_DIR) -I$(LIB_DIR)/libft -I$(LIB_DIR)/ft_printf -I$(LIB_DIR)/get_next_line -I$(MLX_DIR)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Sources / objets
SRCS         = \
	src/algo/bressenham.c \
	src/algo/calculate.c \
	src/algo/trace.c \
	src/dda/frame.c \
	src/dda/raycast.c \
	src/dda/raycast_utils.c \
	src/main.c \
	src/mlx/mlx_utils.c \
	src/mlx/put_pixel.c \
	src/parse/add_textures.c \
	src/parse/character.c \
	src/parse/colors.c \
	src/parse/law.c \
	src/parse/parsing_map.c \
	src/parse/scan_map.c \
	src/utils/block.c \
	src/utils/errors.c \
	src/utils/free.c \
	src/utils/init_walls.c \
	src/utils/keys.c \
	src/utils/maps.c \
	src/utils/move.c \
	src/utils/strings.c\
	src/bonus/mouse_movements.c\
	src/bonus/mousse_utils.c \
	src/bonus/minimap.c
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Couleurs
GREEN		= \033[0;32m
RESET		= \033[0m

# Règles
all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $@ $(MLX_FLAGS)
	@echo "$(GREEN)[OK]$(RESET)✅ Compilation terminée."

$(LIBFT):
	@$(MAKE) -sC $(LIB_DIR)
	
$(MLX_LIB):
	@$(MAKE) -sC $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -sC $(LIB_DIR) clean
	@$(MAKE) -sC $(MLX_DIR) clean
	@echo "$(GREEN)[OK]$(RESET) Clean."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re update
