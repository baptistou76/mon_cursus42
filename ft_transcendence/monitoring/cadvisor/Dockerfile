FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/cadvisor

RUN wget https://github.com/google/cadvisor/releases/download/v0.49.1/cadvisor-v0.49.1-linux-amd64 \
 && chmod +x cadvisor-v0.49.1-linux-amd64 \
 && mv cadvisor-v0.49.1-linux-amd64 cadvisor

EXPOSE 8080

CMD ["./cadvisor"]