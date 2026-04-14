NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

GREEN       = \033[32m
RED         = \033[31m

SRC_DIR = src_bonus/
OBJ_DIR = obj/

SRC = src_bonus/init.c\
	  src_bonus/list.c\
	  src_bonus/main.c\
	  src_bonus/process.c\
	  src_bonus/time_is_on_my_side.c\
	  src_bonus/free.c\
	  src_bonus/utils.c\
	  src_bonus/routine.c\

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

TOTAL_FILES = $(words $(SRC))
COMPILED    = 0

define update_progress
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
    @printf "\r$(GREEN)Compiling [%-50s] %d%% (%d/%d)$(RESET)" \
        "$$(printf '█%.0s' $$(seq 1 $$(($(COMPILED)*50/$(TOTAL_FILES)))))" \
        $$(($(COMPILED)*100/$(TOTAL_FILES))) \
        $(COMPILED) \
        $(TOTAL_FILES)
endef

all: $(NAME)
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\n$(RED)✅ Compilation terminee : $(NAME)$(RESET)" 
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(update_progress)
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
clean:
	@rm -rf $(OBJ_DIR)
fclean: clean
	@rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re