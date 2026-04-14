#!/bin/sh
set -eu

ES="https://elasticsearch:9200"
CACERT="/certs/ca/ca.crt"

: "${ELASTIC_PASSWORD:=elasticpass}"
: "${KIBANA_PASSWORD:=kibanapass}"

echo "[elk-setup] Waiting for Elasticsearch (HTTPS)..."
until curl -fsS --cacert "$CACERT" -u "elastic:${ELASTIC_PASSWORD}" "$ES" >/dev/null 2>&1; do
  sleep 2
done

echo "[elk-setup] Setting kibana_system password..."
curl -fsS --cacert "$CACERT" -u "elastic:${ELASTIC_PASSWORD}" \
  -X POST "$ES/_security/user/kibana_system/_password" \
  -H "Content-Type: application/json" \
  -d "{\"password\":\"${KIBANA_PASSWORD}\"}" >/dev/null

echo "[elk-setup] Creating ILM policy (14 days retention)..."
curl -fsS --cacert "$CACERT" -u "elastic:${ELASTIC_PASSWORD}" \
  -X PUT "$ES/_ilm/policy/logs_policy" \
  -H 'Content-Type: application/json' \
  -d '{
    "policy": {
      "phases": {
        "hot": { "actions": {} },
        "delete": { "min_age": "14d", "actions": { "delete": {} } }
      }
    }
  }' >/dev/null

echo "[elk-setup] Creating index template logs-* ..."
curl -fsS --cacert "$CACERT" -u "elastic:${ELASTIC_PASSWORD}" \
  -X PUT "$ES/_index_template/logs_template" \
  -H 'Content-Type: application/json' \
  -d '{
    "index_patterns": ["logs-*"],
    "template": {
      "settings": { "index.lifecycle.name": "logs_policy" }
    }
  }' >/dev/null

echo "[elk-setup] Done."
