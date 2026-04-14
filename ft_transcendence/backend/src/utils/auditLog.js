import fs from "fs";
import path from "path";
import { fileURLToPath } from "url";
import { dirname, join } from "path";

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);
const LOG_FILE = process.env.LOG_FILE || join(__dirname, "../../..", "logs", "app.log");

function safeString(v) {
  if (v === undefined || v === null) return null;
  return String(v);
}

export function audit(event) {
  try {
    const dir = path.dirname(LOG_FILE);
    if (!fs.existsSync(dir)) fs.mkdirSync(dir, { recursive: true });

    const line = JSON.stringify({
      "@timestamp": new Date().toISOString(),
      ...event,
    });

    fs.appendFileSync(LOG_FILE, line + "\n", "utf8");
  } catch (e) {
    // volontairement silencieux : on ne casse jamais le backend à cause des logs
  }
}

export function auditAuth({ action, user, request, extra = {} }) {
  audit({
    "event.category": "auth",
    "event.action": action,
    "user.id": user?.id ?? null,
    "user.display_name": safeString(user?.display_name ?? user?.displayName),
    "client.ip": request?.ip ?? request?.headers?.["x-forwarded-for"]?.split(",")[0] ?? null,
    "user_agent.original": request?.headers?.["user-agent"] ?? null,
    ...extra,
  });
}

export function auditMatch({ action, match, extra = {} }) {
  audit({
    "event.category": "game",
    "event.action": action,
    "match.id": match?.id ?? null,
    "match.player1_id": match?.player1_id ?? null,
    "match.player2_id": match?.player2_id ?? null,
    "match.winner_id": match?.winner_id ?? null,
    "match.score.p1": match?.details?.score?.player1 ?? null,
    "match.score.p2": match?.details?.score?.player2 ?? null,
    ...extra,
  });
}
