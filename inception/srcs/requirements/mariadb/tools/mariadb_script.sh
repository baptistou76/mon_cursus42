#!/bin/sh

# Démarrer MariaDB en background
mysqld_safe &

# Attendre que MariaDB soit prêt
while ! mysqladmin ping --silent; do
    sleep 1
done

mysql -u root << EOF
CREATE DATABASE IF NOT EXISTS \`${SQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${SQL_USER}'@'%' IDENTIFIED BY '${SQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${SQL_DATABASE}\`.* TO '${SQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF

# Garder MariaDB au premier plan
wait
