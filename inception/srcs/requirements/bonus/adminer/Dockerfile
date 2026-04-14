FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    php \
    php-mysql \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Télécharger Adminer
RUN wget https://www.adminer.org/latest.php -O /var/www/html/index.php

WORKDIR /var/www/html

EXPOSE 8080

CMD ["php", "-S", "0.0.0.0:8080"]