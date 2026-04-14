FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/alertmanager

RUN wget https://github.com/prometheus/alertmanager/releases/download/v0.27.0/alertmanager-0.27.0.linux-amd64.tar.gz \
 && tar xvf alertmanager-0.27.0.linux-amd64.tar.gz \
 && mv alertmanager-0.27.0.linux-amd64 alertmanager \
 && rm alertmanager-0.27.0.linux-amd64.tar.gz

EXPOSE 9093

CMD ["./alertmanager/alertmanager", \
     "--config.file=/etc/alertmanager/alertmanager.yml"]
	 