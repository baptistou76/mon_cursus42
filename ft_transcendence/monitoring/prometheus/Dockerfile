FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
	wget \
	ca-certificates \
	&& rm -rf /var/lib/apt/list/*

WORKDIR /opt/prometheus

RUN wget https://github.com/prometheus/prometheus/releases/download/v2.49.1/prometheus-2.49.1.linux-amd64.tar.gz \
	&& tar xvf prometheus-2.49.1.linux-amd64.tar.gz \
	&& mv prometheus-2.49.1.linux-amd64 prometheus \
	&& rm prometheus-2.49.1.linux-amd64.tar.gz

EXPOSE 9090

CMD ["./prometheus/prometheus", \
     "--config.file=/etc/prometheus/prometheus.yml", \
     "--web.external-url=/prometheus", \
     "--web.route-prefix=/", \
     "--storage.tsdb.path=/prometheus", "--storage.tsdb.retention.time=7d"]
