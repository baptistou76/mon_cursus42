import fs from "fs";
import path from "path";

const LOG_FILE = process.env.GAME_LOG_FILE || "/app/logs/game/events.jsonl";

let stream = null;

function ensureStream() {
  if (stream) return;
  const dir = path.dirname(LOG_FILE);
  if (!fs.existsSync(dir)) fs.mkdirSync(dir, { recursive: true });
  stream = fs.createWriteStream(LOG_FILE, { flags: "a" });
}

export function gameLog(event) {
  try {
    ensureStream();
    const payload = {
      "@timestamp": new Date().toISOString(),
      "service.name": "backend",
      ...event,
    };
    stream.write(JSON.stringify(payload) + "\n");
  } catch {
  }
}
