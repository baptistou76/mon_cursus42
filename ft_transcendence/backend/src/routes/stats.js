import db, { getSessionByJti, findUserById, getUserRecentMatches, getUserMatchesCount, findMatchById } from "../db.js";
import { getAvatarUrl } from "../utils/avatar.js";

export default async function (fastify, options) {
  // GET /me/stats -> { wins, losses }
  fastify.get(
    "/me/stats",
    {
      schema: {
        response: {
          200: {
            type: "object",
            properties: {
              wins: { type: "number" },
              losses: { type: "number" },
            },
            required: ["wins", "losses"],
          },
        },
      },
    },
    async (request, reply) => {
      if (!request.user || !request.user.jti) {
        return reply.status(401).send({ error: "Unauthorized" });
      }
      const session = getSessionByJti(request.user.jti);
      if (!session) return reply.status(401).send({ error: "Session not found" });
      const user = findUserById(session.user_id);
      if (!user) return reply.status(404).send({ error: "User not found" });

      const winsRow = db
        .prepare(
          `SELECT COUNT(1) AS wins
           FROM matches
           WHERE (player1_id = ? OR player2_id = ?)
             AND winner_id = ?`
        )
        .get(user.id, user.id, user.id);

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
        .get(user.id, user.id, user.id);

      return reply.send({
        wins: winsRow?.wins || 0,
        losses: lossesRow?.losses || 0,
      });
    }
  );

  // GET /me/history -> recent 1v1 matches list with pagination
  fastify.get(
    "/me/history",
    {
      schema: {
        querystring: {
          type: "object",
          properties: { 
            limit: { type: "integer", minimum: 1, maximum: 50 },
            page: { type: "integer", minimum: 1 }
          },
        },
        response: {
          200: {
            type: "object",
            properties: {
              matches: {
                type: "array",
                items: {
                  type: "object",
                  properties: {
                    id: { type: "number" },
                    played_at: { type: "string" },
                    player1_id: { type: "number" },
                    player2_id: { type: "number" },
                    winner_id: { type: ["number", "null"] },
                    result: { type: "string" },
                    opponent: {
                      type: "object",
                      properties: {
                        id: { type: "number" },
                        display_name: { type: ["string", "null"] },
                        avatar: { type: ["string", "null"] },
                      },
                      required: ["id"],
                    },
                    details: {},
                  },
                  required: ["id", "played_at", "player1_id", "player2_id", "result", "opponent"],
                },
              },
              total: { type: "number" },
              page: { type: "number" },
              limit: { type: "number" },
              totalPages: { type: "number" }
            },
            required: ["matches", "total", "page", "limit", "totalPages"],
          },
        },
      },
    },
    async (request, reply) => {
      if (!request.user || !request.user.jti) {
        return reply.status(401).send({ error: "Unauthorized" });
      }
      const session = getSessionByJti(request.user.jti);
      if (!session) return reply.status(401).send({ error: "Session not found" });
      const user = findUserById(session.user_id);
      if (!user) return reply.status(404).send({ error: "User not found" });

      const limit = typeof request.query?.limit === "number" ? request.query.limit : 10;
      const page = typeof request.query?.page === "number" ? request.query.page : 1;
      const offset = (page - 1) * limit;
      
      const total = getUserMatchesCount(user.id);
      const totalPages = Math.ceil(total / limit);
      const matches = getUserRecentMatches(user.id, limit, offset);

      const enriched = matches.map((m) => {
        const opponentId = m.player1_id === user.id ? m.player2_id : m.player1_id;
        const full = findMatchById(m.id);
        let result = "draw";
        if (m.winner_id) {
          result = m.winner_id === user.id ? "win" : "loss";
        } else if (full && full.winner_alias) {
          result = full.winner_alias === user.display_name ? "win" : "loss";
        }

        const opponentUser = opponentId ? findUserById(opponentId) : null;
        const opponentDisplay = opponentUser?.display_name ?? (
          m.player1_id === user.id ? full?.player2_alias : full?.player1_alias
        ) ?? null;
        const opponentAvatar = opponentUser ? getAvatarUrl(opponentUser.avatar) : getAvatarUrl(null);
        const opponentResolvedId = opponentUser?.id ?? 0;

        return {
          id: m.id,
          played_at: m.played_at ? m.played_at + 'Z' : null,
          player1_id: m.player1_id,
          player2_id: m.player2_id,
          winner_id: m.winner_id ?? null,
          opponent: { id: opponentResolvedId, display_name: opponentDisplay, avatar: opponentAvatar },
          result,
          details: m.details ?? null,
        };
      });

      return reply.send({
        matches: enriched,
        total,
        page,
        limit,
        totalPages
      });
    }
  );
}
