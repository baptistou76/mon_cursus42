FROM debian:bullseye

ARG FTP_USER
ARG FTP_PASSWORD

# Installer vsftpd
RUN apt-get update && \
    apt-get install -y vsftpd && \
    rm -rf /var/lib/apt/lists/*

# Copier le fichier de configuration
COPY ./conf/vsftpd.conf /etc/vsftpd.conf


# Créer un utilisateur FTP avec home dans WordPress et définir son mot de passe
RUN useradd -m -d /var/www/html/wordpress $FTP_USER && \
    echo "$FTP_USER:$FTP_PASSWORD" | chpasswd && \
    mkdir -p /var/run/vsftpd/empty && \
    chmod 755 /var/run/vsftpd/empty && \
    chown -R $FTP_USER:www-data /var/www/html/wordpress && \
    chmod 775 /var/www/html/wordpress && \
    usermod -aG www-data $FTP_USER

EXPOSE 21 21000-21010

# Lancer vsftpd en mode foreground (standalone)
CMD ["/usr/sbin/vsftpd", "/etc/vsftpd.conf"]