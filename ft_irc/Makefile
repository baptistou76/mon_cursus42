# === CONFIGURATION ===
NAME        = ircserv
CPP         = c++
CPPFLAGS    = -Wall -Wextra -Werror -std=c++98 -Iclasses -Iclasses/cmds

# === COULEURS ===
RESET       = \033[0m
GREEN       = \033[32m
RED         = \033[31m
YELLOW      = \033[33m

# === RÉPERTOIRES ===
SRC_DIR     = srcs
OBJ_DIR     = obj

# === SOURCES ===
SRC         = \
	srcs/Channel.cpp \
	srcs/Client.cpp \
	srcs/cmds/PassCmd.cpp \
	srcs/cmds/InviteCmd.cpp \
	srcs/cmds/JoinCmd.cpp \
	srcs/cmds/KickCmd.cpp \
	srcs/cmds/ModeCmd.cpp \
	srcs/cmds/NickCmd.cpp \
	srcs/cmds/PrivMsgCmd.cpp \
	srcs/cmds/TopicCmd.cpp \
	srcs/cmds/PingCmd.cpp \
	srcs/cmds/UserCmd.cpp \
	srcs/CommandHandler.cpp \
	srcs/cmds/PartCmd.cpp \
	srcs/cmds/QuitCmd.cpp \
	srcs/cmds/CapCmd.cpp \
	srcs/main.cpp \
	srcs/Mode.cpp \
	srcs/Server.cpp \
	srcs/Topic.cpp \
	srcs/Utils.cpp \
	srcs/signal.cpp

OBJ         = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)



# === PROGRESS BAR ===
TOTAL_FILES = $(words $(SRC))
COMPILED    = 0

define update_progress
	@$(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@printf "\r$(YELLOW)Compiling [%-50s] %d%% (%d/%d)$(RESET)" \
		"$$(printf '█%.0s' $$(seq 1 $$(($(COMPILED)*50/$(TOTAL_FILES)))))" \
		$$(($(COMPILED)*100/$(TOTAL_FILES))) \
		$(COMPILED) \
		$(TOTAL_FILES)
endef

# === RÈGLES ===

all: $(NAME)

$(NAME): $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@echo "\n$(GREEN)✅ Compilation terminée : $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CPP) $(CPPFLAGS) -c $< -o $@
	$(update_progress)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)🧹 Fichiers objets supprimés$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🧨 Exécutable supprimé$(RESET)"

re: fclean all

update:
	@bash -c '\
		echo "Mise à jour de la liste des fichiers sources..."; \
		find $(SRC_DIR) -type f -name '\''*.cpp'\'' | sort | \
		sed '\''s/^/	/'\'' | sed '\''s/$$/ \\\\/'\'' > .sources_block; \
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
		echo "$(GREEN)✅ Makefile mis à jour$(RESET)"; \
	'

.PHONY: all clean fclean re update
