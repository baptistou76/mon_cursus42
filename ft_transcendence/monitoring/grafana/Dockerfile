FROM grafana/grafana:10.3.1

USER root

COPY defaults.ini /etc/grafana/grafana.ini
COPY entrypoint.sh /entrypoint.sh

RUN chown 472:472 /etc/grafana/grafana.ini && \
	chmod 644 /etc/grafana/grafana.ini && \
	chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]