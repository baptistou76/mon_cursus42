// backend/migrate.js
import fs from "fs";
import path from "path";
import Database from "better-sqlite3";

const DATA_DIR = path.join(process.cwd(), "data");
const DB_PATH = path.join(DATA_DIR, "data.db");

if (!fs.existsSync(DATA_DIR)) {
  fs.mkdirSync(DATA_DIR, { recursive: true });
  console.log("Created data directory:", DATA_DIR);
}

const db = new Database(DB_PATH);
console.log("Opening DB at", DB_PATH);

db.pragma("journal_mode = WAL");
db.pragma("foreign_keys = ON");

db.exec(`
-- Users: registered users (for Standard User Management)
CREATE TABLE IF NOT EXISTS users (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  email TEXT UNIQUE,
  password_hash TEXT DEFAULT NULL, -- NULL if OAuth only
  first_name TEXT DEFAULT NULL,
  last_name TEXT DEFAULT NULL,
  alias TEXT DEFAULT NULL, -- temporary local players (NULL for registered users)
  display_name TEXT,
  login TEXT,
  avatar TEXT DEFAULT NULL,
  avatar_mime TEXT DEFAULT NULL,
  avatar_size INTEGER DEFAULT NULL,
  avatar_updated_at TEXT DEFAULT NULL,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Sessions: store active sessions / ability to revoke by jti
CREATE TABLE IF NOT EXISTS sessions (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  user_id INTEGER NOT NULL,
  jti TEXT UNIQUE,
  issued_at DATETIME,
  expires_at DATETIME,
  revoked INTEGER DEFAULT 0,
  FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE
);

-- Friends: mutual relations (user -> friend). UNIQUE to avoid duplicates.
CREATE TABLE IF NOT EXISTS friends (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  user_id INTEGER NOT NULL,
  friend_id INTEGER NOT NULL,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  UNIQUE(user_id, friend_id),
  FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE,
  FOREIGN KEY(friend_id) REFERENCES users(id) ON DELETE CASCADE
);

-- Matches: 1v1 games history (used for stats and match history)
-- Supports both registered users (via IDs) and anonymous tournament players (via aliases)
-- details: JSON text for storing score, duration, replay link etc.
CREATE TABLE IF NOT EXISTS matches (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  player1_id INTEGER,                 -- NULLABLE: NULL for anonymous tournament players
  player2_id INTEGER,                 -- NULLABLE: NULL for anonymous tournament players
  player1_alias TEXT,                 -- Alias/display name for player 1
  player2_alias TEXT,                 -- Alias/display name for player 2
  winner_id INTEGER,                  -- NULLABLE: NULL for draw / unfinished / anonymous winner
  winner_alias TEXT,                  -- Alias of winner (for anonymous tournaments)
  played_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  details TEXT,
  FOREIGN KEY(player1_id) REFERENCES users(id),
  FOREIGN KEY(player2_id) REFERENCES users(id),
  FOREIGN KEY(winner_id)  REFERENCES users(id)
);

-- Tournament model:
CREATE TABLE IF NOT EXISTS tournaments (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT,
  status TEXT DEFAULT 'pending',      -- pending | running | finished
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  started_at DATETIME,
  finished_at DATETIME,
  settings TEXT                       -- JSON: rules, paddle_speed, etc.
);

-- Players registered in a tournament.
-- We store display alias per tournament (aliases reset on new tournament)
CREATE TABLE IF NOT EXISTS tournament_players (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  tournament_id INTEGER NOT NULL,
  user_id INTEGER,                    -- optional: NULL if anonymous alias
  alias TEXT NOT NULL,
  slot_order INTEGER DEFAULT 0,       -- order in tournament / queue
  joined_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY(tournament_id) REFERENCES tournaments(id) ON DELETE CASCADE,
  FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE SET NULL,
  UNIQUE(tournament_id, alias)
);

-- Tournament matches (links matches to a tournament)
CREATE TABLE IF NOT EXISTS tournament_matches (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  tournament_id INTEGER NOT NULL,
  match_id INTEGER NOT NULL,
  match_order INTEGER DEFAULT 0,
  FOREIGN KEY(tournament_id) REFERENCES tournaments(id) ON DELETE CASCADE,
  FOREIGN KEY(match_id) REFERENCES matches(id) ON DELETE CASCADE
);

-- Matchmaking queue (simple queue)
CREATE TABLE IF NOT EXISTS matchmaking_queue (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  tournament_id INTEGER,              -- optional: NULL for casual queue
  user_id INTEGER,
  alias TEXT,
  enqueued_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE SET NULL
);

-- Blocked Users: who (user_id) blocked whom (blocked_id)
CREATE TABLE IF NOT EXISTS blocked_users (
  user_id INTEGER NOT NULL,
  blocked_id INTEGER NOT NULL,
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (user_id, blocked_id),
  FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE,
  FOREIGN KEY(blocked_id) REFERENCES users(id) ON DELETE CASCADE
);

-- Indexes to accelerate lookups
CREATE INDEX IF NOT EXISTS idx_matches_player1 ON matches(player1_id);
CREATE INDEX IF NOT EXISTS idx_matches_player2 ON matches(player2_id);
CREATE INDEX IF NOT EXISTS idx_matches_played_at ON matches(played_at);
CREATE INDEX IF NOT EXISTS idx_tournament_players_tourn ON tournament_players(tournament_id);
CREATE INDEX IF NOT EXISTS idx_sessions_jti ON sessions(jti);
CREATE INDEX IF NOT EXISTS idx_friends_user ON friends(user_id);

-- Trigger to update user's updated_at on modify
CREATE TRIGGER IF NOT EXISTS trg_users_updated_at
AFTER UPDATE ON users
BEGIN
  UPDATE users SET updated_at = CURRENT_TIMESTAMP WHERE id = NEW.id;
END;
`);

console.log("Migrations applied (tables + indexes + triggers).");

const row = db.prepare("SELECT count(name) as cnt FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%'").get();
console.log("Tables present:", row.cnt);

db.close();
console.log("DB closed. Done.");
