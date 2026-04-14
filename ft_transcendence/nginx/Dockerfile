FROM nginx

RUN mkdir -p /etc/nginx/ssl \
    && openssl req -x509 -newkey rsa:2048 -nodes \
        -keyout /etc/nginx/ssl/localhost.key \
        -out /etc/nginx/ssl/localhost.crt \
        -days 365 \
        -subj "/C=FR/ST=Normandie/L=LeHavre/O=42/OU=Transcendence/CN=localhost" \
        -addext "subjectAltName=DNS:localhost"

COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY conf/.htpasswd /etc/nginx/.htpasswd
