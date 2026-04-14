#!/usr/bin/env bash
set -euo pipefail

CERTS_DIR="/usr/share/elasticsearch/config/certs"

if [ -f "${CERTS_DIR}/ca/ca.crt" ] && [ -f "${CERTS_DIR}/elasticsearch/elasticsearch.crt" ] && [ -f "${CERTS_DIR}/kibana/kibana.crt" ]; then
  echo "[elk-certs] certs already exist"
  exit 0
fi

echo "[elk-certs] generating CA + certs..."
mkdir -p "${CERTS_DIR}"

cat > "${CERTS_DIR}/instances.yml" <<'YML'
instances:
  - name: elasticsearch
    dns: [ "elasticsearch", "localhost" ]
    ip: [ "127.0.0.1" ]
  - name: kibana
    dns: [ "kibana", "localhost" ]
    ip: [ "127.0.0.1" ]
YML

/usr/share/elasticsearch/bin/elasticsearch-certutil ca --silent --pem -out "${CERTS_DIR}/ca.zip"
unzip -qo "${CERTS_DIR}/ca.zip" -d "${CERTS_DIR}"

 /usr/share/elasticsearch/bin/elasticsearch-certutil cert --silent --pem \
  --in "${CERTS_DIR}/instances.yml" \
  --ca-cert "${CERTS_DIR}/ca/ca.crt" \
  --ca-key "${CERTS_DIR}/ca/ca.key" \
  -out "${CERTS_DIR}/certs.zip"

unzip -qo "${CERTS_DIR}/certs.zip" -d "${CERTS_DIR}"

rm -f "${CERTS_DIR}/ca.zip" "${CERTS_DIR}/certs.zip" "${CERTS_DIR}/instances.yml"

chown -R 1000:0 "${CERTS_DIR}"
chmod -R g+rX "${CERTS_DIR}"

echo "[elk-certs] done"
