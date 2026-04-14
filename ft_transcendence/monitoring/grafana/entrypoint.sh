#!/bin/bash

# Fix permissions on mounted volumes
chown -R grafana:grafana /etc/grafana/provisioning 2>/dev/null || true
chmod -R 755 /etc/grafana/provisioning 2>/dev/null || true

# Execute the original entrypoint
exec /run.sh "$@"
