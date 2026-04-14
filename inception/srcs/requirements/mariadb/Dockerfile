# Utiliser Debian 11 (Bullseye) comme image de base
FROM debian:bullseye

# Mettre à jour la liste des paquets
RUN apt-get update -y && apt-get -y upgrade && \
    apt-get install -y wget lsb-release gnupg \
    mariadb-server mariadb-client procps \
    && rm -rf /var/lib/apt/lists/* && \
    mkdir -p /var/lib/mysql && \
    mkdir -p /var/run/mysqld

# Copier le fichier de configuration personnalisé de MariaDB
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Attribuer les permissions à l'utilisateur MySQL pour le répertoire PID
RUN chown mysql:mysql /var/run/mysqld/

# Donner des permissions de lecture/écriture/exécution au répertoire PID
RUN chmod -R 755 /var/run/mysqld/

# Attribuer les permissions à l'utilisateur MySQL pour le répertoire des données
RUN chown mysql:mysql /var/lib/mysql/

# Donner des permissions de lecture/écriture/exécution au répertoire des données
RUN chmod -R 755 /var/lib/mysql/

# Exposer le port 3306 pour les connexions MariaDB
EXPOSE 3306

# Copier le script d'initialisation dans l'image
COPY ./tools/mariadb_script.sh .

# Rendre le script d'initialisation exécutable
RUN chmod +x ./mariadb_script.sh

# Définir le point d'entrée pour lancer le script d'initialisation
ENTRYPOINT ["./mariadb_script.sh"]
