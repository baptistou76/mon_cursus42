DOCKER_COMPOSE = docker compose
PROJECT_NAME = ft_transcendence

# ifeq ($(OS), Darwin)
#     SERVER_IP = $(shell ifconfig | grep "inet " | grep -v 127.0.0.1 | awk '{print $$2}' | head -n 1)
#     SED_I = sed -i ""
# else
#     SERVER_IP = $(shell hostname -i)
#     SED_I = sed -i
# endif

# FORTYTWO_REDIRECT_URI=https://$(SERVER_IP):443/api/auth/42/callback
# FRONTEND_URL=https://$(SERVER_IP):443
# VITE_API_URL=https://$(SERVER_IP):443/api
# VISUAL_DB_PATH=/home/rureshet/Documents/VisualDB
SERVER_IP = localhost
.PHONY: start up down build logs restart restart-clean test clean full-clean volumes-list  db-copy front_up front_down front_restart #add_ip add_callback add_frontend add_vite add_to_env

RST    = "\033[0m"
GRAY   = "\033[90m"
GREEN  = "\033[0;32m"
AQUA   = "\033[38;5;116m"
ORANGE = "\033[38;5;215m"
YEL    = "\033[38;2;219;171;121m"
SKY    = "\033[38;2;113;190;242m"

SERVICE_TABLE := \
" ╭──────────────────────────────────────────────────────╮\n"\
"│"$(SKY) "ft_transcendence "$(RST)"                                    │\n"\
"├──────────────┬───────────────────────────────────────┤\n"\
"│ service      │ location                              │\n"\
"├──────────────┼───────────────────────────────────────┤\n"\
"│" $(ORANGE) " Ping Pong: "$(RST)│$(GREEN)" https://$(SERVER_IP)/" $(RST) "\t\t        │\n"\
"├──────────────┼───────────────────────────────────────┤\n"\
"│" $(YEL) "   Grafana: "$(RST)│$(GREEN)" https://$(SERVER_IP)/grafana/" $(RST) "\t\t│\n"\
"├──────────────┼───────────────────────────────────────┤\n"\
"│" $(YEL) "   Kibana:  "$(RST)│$(GREEN)" https://$(SERVER_IP)/kibana/login/" $(RST) "\t│\n"\
"╰──────────────┴───────────────────────────────────────╯\n"


start: 
	$(DOCKER_COMPOSE) up -d --build
	$(DOCKER_COMPOSE) exec backend node migrate.js
# 	@echo "\n" $(ORANGE) "Ping Pong: " $(GREEN)"https://localhost/"$(RST)"\n"
# 	@echo $(ORANGE) "Grafana dashboard: " $(GREEN)"https://localhost/grafana/"$(RST)"\n"
# 	@echo $(ORANGE) "Kibana dashboard: " $(GREEN)"https://localhost/kibana/login/"$(RST)"\n"
	@echo $(SERVICE_TABLE)

up:
	$(DOCKER_COMPOSE) up --build

front_up:
	$(DOCKER_COMPOSE) up -d --build frontend

down:
	$(DOCKER_COMPOSE) down --timeout 1

front_down:
	$(DOCKER_COMPOSE) down --timeout 1 frontend

build:
	$(DOCKER_COMPOSE) build

logs:
	$(DOCKER_COMPOSE) logs -f

restart: down start

restart-clean: down
	docker builder prune -af
	$(DOCKER_COMPOSE) up -d --build --no-cache
	$(DOCKER_COMPOSE) exec backend node migrate.js
# 	@echo "\n" $(ORANGE) "Ping Pong: " $(GREEN)"https://$(SERVER_IP)/"$(RST)"\n"
	@echo $(SERVICE_TABLE)

front_restart: front_down front_up

test:
	$(DOCKER_COMPOSE) run --rm backend npm test
	$(DOCKER_COMPOSE) run --rm frontend npm test

clean:
	$(DOCKER_COMPOSE) down -v --remove-orphans
	docker system prune -f

full-clean:
	$(DOCKER_COMPOSE) down -v --remove-orphans
	docker volume prune -f
	docker system prune -a -f
	@echo "Full clean completed."

volumes-list:
	@echo "=== Docker Volumes ==="
	docker volume ls
	@echo "=== Project Volumes ==="
	docker volume ls | grep $(PROJECT_NAME) || echo "No project volumes found"

# add_ip:
# 	@echo $(GRAY)"Updating Server ip"
# 	grep -q ^SERVER_IP= .env && $(SED_I) 's/SERVER_IP=.*/SERVER_IP='$(SERVER_IP)'/' .env || echo '\n'SERVER_IP=$(SERVER_IP) >> .env

# add_callback:
# 	grep -q ^FORTYTWO_REDIRECT_URI= .env && $(SED_I) "s/FORTYTWO_REDIRECT_URI=.*/FORTYTWO_REDIRECT_URI=$$(echo $(FORTYTWO_REDIRECT_URI) | sed 's,/,\\/,g')/"  .env || echo FORTYTWO_REDIRECT_URI=$(FORTYTWO_REDIRECT_URI) >> .env

# add_frontend:
# 	grep -q ^FRONTEND_URL= .env && $(SED_I) "s/FRONTEND_URL=.*/FRONTEND_URL=$$(echo $(FRONTEND_URL) | sed 's,/,\\/,g')/"  .env || echo FRONTEND_URL=$(FRONTEND_URL) >> .env

# add_vite:
# 	grep -q ^VITE_API_URL= .env && $(SED_I) "s/VITE_API_URL=.*/VITE_API_URL=$$(echo $(VITE_API_URL) | sed 's,/,\\/,g')/"  .env || echo VITE_API_URL=$(VITE_API_URL) >> .env
# 	@echo -n $(RST);

# add_to_env: add_ip add_callback add_frontend add_vite

db-copy:
	@echo $(GRAY)"Copying database files..."
	docker cp backend:/app/data/data.db $(VISUAL_DB_PATH)
	docker cp backend:/app/data/data.db-shm $(VISUAL_DB_PATH)
	docker cp backend:/app/data/data.db-wal $(VISUAL_DB_PATH)
	@echo -n $(RST)

show_service:
	@echo $(SERVICE_TABLE)