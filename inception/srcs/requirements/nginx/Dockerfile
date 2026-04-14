# Indiquer à Docker l'OS de base pour la machine virtuelle (Debian 11)
FROM debian:bullseye

# Mettre à jour la liste des paquets
RUN apt update -y 

# Installer NGINX
RUN apt install -y nginx

# Installer l'éditeur de texte Vim
RUN apt install -y vim

# Installer l'outil de ligne de commande Curl
RUN apt install -y curl

# Créer le répertoire pour les certificats SSL de NGINX
RUN mkdir -p /etc/nginx/ssl

# Installer OpenSSL pour générer les certificats SSL
RUN apt install -y openssl

# Générer un certificat SSL auto-signé pour NGINX
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=FR/ST=NORMANDIE/L=LE_HAVRE/O=42/OU=42/CN=bcaumont.42.fr/UID=bcaumont"

# Créer le répertoire pour les fichiers PID de NGINX
RUN mkdir -p /var/run/nginx

# Copier le fichier de configuration NGINX personnalisé
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Définir les permissions pour le répertoire web
RUN chmod 755 /var/www/html

# Attribuer les permissions à l'utilisateur NGINX pour le répertoire web
RUN chown -R www-data:www-data /var/www/html

# Lancer NGINX au premier plan pour éviter l'arrêt du conteneur
CMD [ "nginx", "-g", "daemon off;" ]
