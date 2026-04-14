FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y wget && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/prometheus/node_exporter/releases/download/v1.7.0/node_exporter-1.7.0.linux-amd64.tar.gz \
 && tar xvf node_exporter-1.7.0.linux-amd64.tar.gz \
 && mv node_exporter-1.7.0.linux-amd64/node_exporter /usr/local/bin \
 && rm -rf node_exporter-1.7.0*

EXPOSE 9100

CMD ["node_exporter"]