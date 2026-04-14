#!/bin/bash

# Attendre 10 secondes pour s'assurer que la base de données MariaDB est bien démarrée
sleep 10

# Se déplacer dans le répertoire WordPress
cd /var/www/html/wordpress

if [ ! -f /var/www/html/wordpress/wp-config.php ]; then
# Vérifier si WordPress a déjà été configuré
    echo "CREATING CONFIG .... !\n"
    # Crée le fichier wp-config.php avec les informations de connexion à la base de données
    # et configure les paramètres de connexion à la base MariaDB
    wp config create --allow-root \
        --dbname=${SQL_DATABASE} \
        --dbuser=${SQL_USER} \
        --dbpass=${SQL_PASSWORD} \
        --dbhost=mariadb \
        --path='/var/www/html/wordpress' \
        --url=https://${DOMAIN_NAME}

    # Installe WordPress avec les informations du site (titre, URL) et crée le compte administrateur
    wp core install --allow-root \
        --path='/var/www/html/wordpress' \
        --url=https://${DOMAIN_NAME} \
        --title=${SITE_TITLE} \
        --admin_user=${ADMIN_USER} \
        --admin_password=${ADMIN_PASSWORD} \
        --admin_email=${ADMIN_EMAIL}

    # Créer un second utilisateur WordPress avec le rôle "auteur"
    wp user create --allow-root \
        ${SECOND_USER} ${SECOND_USER_EMAIL} \
        --role=author \
        --user_pass=${SECOND_USER_PASSWORD}

    # wp config set WP_DEBUG true
    wp config set FORCE_SSL_ADMIN false --allow-root --raw
    wp config  set WP_REDIS_HOST $WP_REDIS_HOST --allow-root
    wp config set WP_REDIS_PORT $WP_REDIS_PORT --raw --allow-root
    wp config  set WP_CACHE true --allow-root --raw
    wp plugin install redis-cache --allow-root
    wp plugin activate redis-cache --allow-root
    wp redis enable --allow-root

    chmod 777 /var/www/html/wordpress

    # install theme
    wp theme install twentyfifteen --allow-root
    wp theme activate twentyfifteen --allow-root
    wp theme update twentyfifteen --allow-root


    # Vider le cache WordPress
    wp cache flush --allow-root

    echo "wp-config created successfully !"
fi

# Vérifier si le répertoire /run/php n'existe pas, et le créer si nécessaire
if [ ! -d /run/php ]; then
    mkdir /run/php
fi

# Lancer php-fpm en mode premier plan pour éviter que le conteneur ne se termine
exec /usr/sbin/php-fpm7.4 -F -R
