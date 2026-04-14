# === CONFIGURATION ===
NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I includes/ -g3

# === COULEURS ===
RESET       = \033[0m
GREEN       = \033[32m
RED         = \033[31m
YELLOW      = \033[33m

# === RÉPERTOIRES ===
SRC_DIR     = src
OBJ_DIR     = obj
LIB_DIR     = lib
LIB_A       = $(LIB_DIR)/libft.a

# === SOURCES === (mise à jour automatique via `make update`)
SRC         = \
	src/builtins/ft_cd.c \
	src/builtins/ft_echo.c \
	src/builtins/ft_env.c \
	src/builtins/ft_exit.c \
	src/builtins/ft_export.c \
	src/builtins/ft_export_utils.c \
	src/builtins/ft_pwd.c \
	src/builtins/ft_unset.c \
	src/exec/cmd_checker.c \
	src/exec/exec.c \
	src/exec/exec_child_process.c \
	src/exec/exec_redir.c \
	src/exec/executables.c \
	src/exec/exec_util.c \
	src/exec/fds.c \
	src/exec/handle_exec.c \
	src/exec/here_doc.c \
	src/exec/infile.c \
	src/exec/outfile.c \
	src/exec/pathfinder.c \
	src/mains/errors.c \
	src/mains/exit_cleaners.c \
	src/mains/free.c \
	src/mains/free_cmd_list.c \
	src/mains/init.c \
	src/mains/main.c \
	src/mains/others2.c \
	src/mains/others.c \
	src/mains/print_errors.c \
	src/mains/signals.c \
	src/mains/utils.c \
	src/parsing/add_arg_and_redir.c \
	src/parsing/env_token.c \
	src/parsing/expand.c \
	src/parsing/lexer.c \
	src/parsing/parse.c \
	src/parsing/quotes.c \
	src/parsing/token_checker.c
OBJ         = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# === PROGRESS BAR ===
TOTAL_FILES = $(words $(SRC))
COMPILED    = 0

define update_progress
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@printf "\r$(RED)Compiling [%-50s] %d%% (%d/%d)$(RESET)" \
		"$$(printf '█%.0s' $$(seq 1 $$(($(COMPILED)*50/$(TOTAL_FILES)))))" \
		$$(($(COMPILED)*100/$(TOTAL_FILES))) \
		$(COMPILED) \
		$(TOTAL_FILES)
endef

# === RÈGLES ===

all: $(NAME)

$(NAME): $(OBJ) | $(LIB_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_A) -o $(NAME) -lreadline
	@echo "\n$(RESET)✅ Compilation terminée : $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(update_progress)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIB_A):
	@$(MAKE) -sC $(LIB_DIR)

update:
	@bash -c '\
		IGNORED_DIRS=("build" "test"); \
		FIND_CMD="find $(SRC_DIR) -type f -name '\''*.c'\''"; \
		for dir in "$${IGNORED_DIRS[@]}"; do \
			FIND_CMD+=" ! -path '\''$(SRC_DIR)/$$dir/*'\''"; \
		done; \
		SOURCE_LIST=$$(eval "$$FIND_CMD" | sort); \
		eval "$$FIND_CMD" | sort | awk '\''{print "\t" $$0 " \\"}'\'' \
		| sed '\''$$ s/ \\$$//'\'' > .sources_block; \
		echo "SRC         = \\" > .sources_full; \
		cat .sources_block >> .sources_full; \
		awk '\'' \
			FNR==NR { lines[NR] = $$0; next } \
			/^SRC[[:space:]]*=/{ \
				for (i=1; i<=length(lines); i++) print lines[i]; \
				in_block=1; next \
			} \
			in_block && /^[^[:space:]]/ { in_block=0 } \
			!in_block { print } \
		'\'' .sources_full Makefile > Makefile.tmp; \
		mv Makefile.tmp Makefile; \
		rm -f .sources_block .sources_full; \
		echo "✅ Makefile mis à jour avec les fichiers sources"; \
	'

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -sC $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -sC $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re update
