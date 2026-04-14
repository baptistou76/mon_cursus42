FROM debian:bullseye

RUN apt-get update \
&& apt-get install -y redis-server \
&& rm -rf /var/lib/apt/lists/*

COPY ./tools/redis.conf /etc/redis/tools/redis.conf

EXPOSE 6379

CMD ["redis-server", "/etc/redis/tools/redis.conf"]
