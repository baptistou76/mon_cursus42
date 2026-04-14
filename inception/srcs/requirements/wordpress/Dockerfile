# Utiliser Debian 11 (Bullseye) comme image de base
FROM debian:bullseye

# Mettre à jour la liste des paquets
RUN apt-get update -y

# Mettre à niveau les paquets installés
RUN apt-get upgrade -y

# Installer wget pour télécharger des fichiers
RUN apt-get install -y wget

# Installer PHP 7.4, PHP-FPM, et le module PHP pour MySQL
RUN apt-get install -y php7.4 \
    php-fpm \
    php-mysql \
    sendmail \
    curl \
    ftp

# Installer WP-CLI pour la gestion de WordPress en ligne de commande
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

# Installer le client MySQL par défaut pour les opérations sur la base de données
RUN apt-get update && apt-get install -y default-mysql-client

# Installer le client MariaDB pour les opérations sur la base de données
RUN apt-get install -y mariadb-client

# Télécharger WordPress et le placer dans le répertoire /var/www/html
RUN wget https://wordpress.org/wordpress-6.1.1.tar.gz -P /var/www/html

# Extraire WordPress et supprimer le fichier téléchargé
RUN cd /var/www/html && \
    tar -xzf /var/www/html/wordpress-6.1.1.tar.gz && \
    rm /var/www/html/wordpress-6.1.1.tar.gz

# Changer les permissions pour le répertoire /var/www
RUN chown -R www-data:www-data /var/www/html/wordpress
RUN chmod -R 775 /var/www/html/wordpress

# Exposer le port 9000 pour PHP-FPM
EXPOSE 9000

# Copier le script d'auto-configuration dans l'image
COPY ./tools/auto_config.sh .

# Rendre le script d'auto-configuration exécutable
RUN chmod +x ./auto_config.sh

# Copier le fichier de configuration personnalisé pour PHP-FPM
COPY ./conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# Définir le point d'entrée pour lancer le script d'auto-configuration
ENTRYPOINT ["./auto_config.sh"]
