
import Database from "better-sqlite3";
import path from "path";
import fs from "fs";

const DATA_DIR = path.join(process.cwd(), "data");
if (!fs.existsSync(DATA_DIR)) fs.mkdirSync(DATA_DIR, { recursive: true });
const DB_PATH = path.join(DATA_DIR, "data.db");

const db = new Database(DB_PATH);
db.pragma("journal_mode = WAL");
db.pragma("foreign_keys = ON");

// -- Users
export function findUserByEmail(email) {
  return db.prepare("SELECT * FROM users WHERE email = ?").get(email);
}
export function findUserById(id) {
  return db.prepare("SELECT * FROM users WHERE id = ?").get(id);
}
export function findUserByDisplayName(display_name) {
  return db.prepare("SELECT * FROM users WHERE display_name = ?").get(display_name);
}
export function searchUsersByDisplayName(searchTerm) {
  const stmt = db.prepare(`
    SELECT id, display_name, avatar, email
    FROM users 
    WHERE display_name LIKE ?
    ORDER BY display_name
    LIMIT 20
  `);
  return stmt.all(`%${searchTerm}%`);
}
export function createUser({ email, login, password_hash = null, first_name = null, last_name = null, display_name = null, avatar = null }) {
  const stmt = db.prepare(`INSERT INTO users (email, login, password_hash, first_name, last_name, display_name, avatar) VALUES (?,?,?,?,?,?,?)`);
  const info = stmt.run(email, login, password_hash, first_name, last_name, display_name, avatar);
  return findUserById(info.lastInsertRowid);
}
export function upsertUserByEmail({ email, login, first_name, last_name, display_name, avatar }) {
  const existing = findUserByEmail(email);
  if (existing) {
    db.prepare(`UPDATE users SET login = ?, first_name = ?, last_name = ?, display_name = ?, avatar = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?`)
      .run(login || existing.login, first_name || existing.first_name, last_name || existing.last_name, display_name || existing.display_name, avatar || existing.avatar, existing.id);
	console.log("Created/updated user:", display_name || existing.display_name);
    return findUserById(existing.id);
  } else {
    return createUser({ email, login, password_hash: null, first_name, last_name, display_name, avatar });
  }
}

export function updateUserById(id, updates) {
  const fields = [];
  const values = [];
  for (const [key, value] of Object.entries(updates)) {
	fields.push(`${key} = ?`);
	values.push(value);
  }
  values.push(id);
  const stmt = db.prepare(`UPDATE users SET ${fields.join(", ")}, updated_at = CURRENT_TIMESTAMP WHERE id = ?`);
  stmt.run(...values);
  return findUserById(id);
}


// -- Sessions
export function saveSession({ user_id, jti, issued_at, expires_at }) {
  return db.prepare(`INSERT INTO sessions (user_id, jti, issued_at, expires_at) VALUES (?,?,?,?)`).run(user_id, jti, issued_at, expires_at);
}
export function getSessionByJti(jti) {
  return db.prepare(`SELECT * FROM sessions WHERE jti = ?`).get(jti);
}
export function revokeSession(jti) {
  return db.prepare(`UPDATE sessions SET revoked = 1 WHERE jti = ?`).run(jti);
}

// -- Friends
export function getFriendsOfUser(user_id) {
    const stmt = db.prepare(`
        SELECT u.id, u.display_name, u.avatar
        FROM friends f
        JOIN users u ON f.friend_id = u.id
        WHERE f.user_id = ?
    `);
    return stmt.all(user_id);
}

export function addFriend(user_id, friend_id) {
    const stmt = db.prepare(`INSERT OR IGNORE INTO friends (user_id, friend_id) VALUES (?,?)`);
    return stmt.run(user_id, friend_id);
}

export function removeFriend(user_id, friend_id) {
    const stmt = db.prepare(`DELETE FROM friends WHERE user_id = ? AND friend_id = ?`);
    return stmt.run(user_id, friend_id);
}

export default db;

// -- Matches / Stats
export function getUserMatchStats(userId) {
  const winsRow = db
    .prepare(
      `SELECT COUNT(1) AS wins
       FROM matches
       WHERE winner_id = ?`
    )
    .get(userId);
  const lossesRow = db
    .prepare(
      `SELECT COUNT(1) AS losses
       FROM matches
       WHERE (player1_id = ? OR player2_id = ?)
         AND (
           (winner_id IS NOT NULL AND winner_id <> ?)
           OR (winner_id IS NULL AND winner_alias IS NOT NULL)
         )`
    )
    .get(userId, userId, userId);
  return {
    wins: winsRow?.wins || 0,
    losses: lossesRow?.losses || 0,
  };
}

export function getUserRecentMatches(userId, limit = 10, offset = 0) {
  const stmt = db.prepare(
    `SELECT id, player1_id, player2_id, player1_alias, player2_alias, winner_id, played_at, details
     FROM matches
     WHERE player1_id = ? OR player2_id = ?
     ORDER BY datetime(played_at) DESC
     LIMIT ? OFFSET ?`
  );
  const rows = stmt.all(userId, userId, limit, offset);
  return rows.map((row) => {
    let details = null;
    if (row.details) {
      try {
        details = JSON.parse(row.details);
      } catch (_) {
        details = row.details;
      }
    }
    return { ...row, details };
  });
}

export function getUserMatchesCount(userId) {
  const stmt = db.prepare(
    `SELECT COUNT(*) as count
     FROM matches
     WHERE player1_id = ? OR player2_id = ?`
  );
  const result = stmt.get(userId, userId);
  return result.count;
}

// -- Blocking
export function blockUser(user_id, blocked_id) {
    const stmt = db.prepare(`INSERT OR IGNORE INTO blocked_users (user_id, blocked_id) VALUES (?, ?)`);
    return stmt.run(user_id, blocked_id);
}

export function unblockUser(user_id, blocked_id) {
    const stmt = db.prepare(`DELETE FROM blocked_users WHERE user_id = ? AND blocked_id = ?`);
    return stmt.run(user_id, blocked_id);
}

// -- Check if user_id has blocked sender_id
export function isUserBlocked(user_id, sender_id) {
    const stmt = db.prepare(`SELECT 1 FROM blocked_users WHERE user_id = ? AND blocked_id = ?`);
    return !!stmt.get(user_id, sender_id);
}

// -- Tournaments
export function createTournament({ name = null, status = 'running', settings = null, started_at = null }) {
  const settingsJson = settings ? JSON.stringify(settings) : null;
  const stmt = db.prepare(
    `INSERT INTO tournaments (name, status, settings, started_at) VALUES (?,?,?,?)`
  );
  const info = stmt.run(name, status, settingsJson, started_at);
  return getTournamentById(info.lastInsertRowid);
}

export function getTournamentById(id) {
  const row = db.prepare(`SELECT * FROM tournaments WHERE id = ?`).get(id);
  if (!row) return null;
  return {
    ...row,
    settings: row.settings ? JSON.parse(row.settings) : null,
  };
}

export function addTournamentPlayer({ tournament_id, user_id, alias, slot_order }) {
  const stmt = db.prepare(
    `INSERT INTO tournament_players (tournament_id, user_id, alias, slot_order) VALUES (?,?,?,?)`
  );
  const info = stmt.run(tournament_id, user_id, alias, slot_order);
  return db.prepare(`SELECT * FROM tournament_players WHERE id = ?`).get(info.lastInsertRowid);
}

export function getTournamentPlayers(tournament_id) {
  return db
    .prepare(
      `SELECT * FROM tournament_players WHERE tournament_id = ? ORDER BY slot_order`
    )
    .all(tournament_id);
}

export function createMatchRecord({ 
  player1_id = null, 
  player2_id = null, 
  player1_alias = null, 
  player2_alias = null, 
  winner_id = null, 
  winner_alias = null,
  details = null 
}) {
  const stmt = db.prepare(
    `INSERT INTO matches (player1_id, player2_id, player1_alias, player2_alias, winner_id, winner_alias, details) 
     VALUES (?,?,?,?,?,?,?)`
  );
  const info = stmt.run(
    player1_id, 
    player2_id, 
    player1_alias, 
    player2_alias, 
    winner_id, 
    winner_alias,
    details ? JSON.stringify(details) : null
  );
  return findMatchById(info.lastInsertRowid);
}

export function findMatchById(id) {
  const row = db.prepare(`SELECT * FROM matches WHERE id = ?`).get(id);
  if (!row) return null;
  return {
    ...row,
    details: row.details ? JSON.parse(row.details) : null,
  };
}

export function linkTournamentMatch({ tournament_id, match_id, match_order = 0 }) {
  const stmt = db.prepare(
    `INSERT INTO tournament_matches (tournament_id, match_id, match_order) VALUES (?,?,?)`
  );
  const info = stmt.run(tournament_id, match_id, match_order);
  return db.prepare(`SELECT * FROM tournament_matches WHERE id = ?`).get(info.lastInsertRowid);
}

export function getTournamentMatches(tournament_id) {
  const rows = db
    .prepare(
      `SELECT tm.id AS tournament_match_id, tm.match_order, m.*
       FROM tournament_matches tm
       JOIN matches m ON m.id = tm.match_id
       WHERE tm.tournament_id = ?
       ORDER BY tm.match_order`
    )
    .all(tournament_id);

  return rows.map((row) => ({
    ...row,
    details: row.details ? JSON.parse(row.details) : null,
  }));
}

export function updateMatchResult(match_id, { winner_id = null, winner_alias = null, details = null }) {
  const existing = findMatchById(match_id);
  if (!existing) return null;

  const mergedDetails = {
    ...(existing.details || {}),
    ...(details || {}),
  };

  db.prepare(`UPDATE matches SET winner_id = ?, winner_alias = ?, details = ? WHERE id = ?`).run(
    winner_id,
    winner_alias,
    mergedDetails ? JSON.stringify(mergedDetails) : null,
    match_id
  );

  return findMatchById(match_id);
}

export function updateTournamentStatus(id, { status, finished_at = null }) {
  db.prepare(`UPDATE tournaments SET status = ?, finished_at = ? WHERE id = ?`).run(
    status,
    finished_at,
    id
  );
  return getTournamentById(id);
}

export function findTournamentMatchByMatchId(tournament_id, match_id) {
  return db
    .prepare(
      `SELECT tm.id AS tournament_match_id, tm.match_order
       FROM tournament_matches tm
       WHERE tm.tournament_id = ? AND tm.match_id = ?`
    )
    .get(tournament_id, match_id);
}