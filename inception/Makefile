NAME        := inception
COMPOSE     := ./srcs/docker-compose.yml
DATA_DIR    := /home/bcaumont/data

all: $(NAME)

$(NAME):
	@mkdir -p $(DATA_DIR)/wordpress $(DATA_DIR)/mariadb
	@docker compose -f $(COMPOSE) build --parallel
	@docker compose -f $(COMPOSE) up -d --build

down:
	@docker compose -f $(COMPOSE) down

clean:
	@docker compose -f $(COMPOSE) down -v

fclean: clean
	@docker system prune --force --volumes --all
	@sudo rm -rf $(DATA_DIR)

re: clean all

logs:
	@echo "__________ MARIADB __________\n"
	@docker compose -f $(COMPOSE) logs mariadb
	@echo "\n__________ WORDPRESS __________\n"
	@docker compose -f $(COMPOSE) logs wordpress
	@echo "\n_________ NGINX ________\n"
	@docker compose -f $(COMPOSE) logs nginx
