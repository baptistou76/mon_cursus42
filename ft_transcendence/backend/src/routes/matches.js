import { createMatchRecord, getSessionByJti, findUserById } from "../db.js";

export default async function matchesRoutes(fastify) {
  fastify.post("/matches", {
    schema: {
      body: {
        type: "object",
        required: ["winner", "score", "opponent_alias", "mode"],
        properties: {
          winner: { type: "string" },
          score: {
            type: "object",
            required: ["left", "right"],
            properties: { left: { type: "number" }, right: { type: "number" } },
          },
          opponent_alias: { type: "string" },
          mode: { type: "string" },
        },
      },
    },
  }, async (request, reply) => {
    try {
      const { winner, score, opponent_alias, mode } = request.body;
      let userId = null;
      if (request.user?.jti) {
        const session = getSessionByJti(request.user.jti);
        if (session) userId = session.user_id;
      }
      if (!userId && request.user?.sub) {
        const parsed = Number(request.user.sub);
        if (!Number.isNaN(parsed)) userId = parsed;
      }
      if (!userId) {
        return reply.code(401).send({ error: "Unauthorized" });
      }
      const dbUser = findUserById(userId);
      if (!dbUser) {
        return reply.code(404).send({ error: "User not found" });
      }

      const player1_id = null;
      const player1_alias = opponent_alias || "Guest";

      const player2_id = dbUser.id;
      const player2_alias = dbUser.display_name || dbUser.login || "User";

      let winner_id = null;
      let winner_alias = "";
      const leftScore = Number(score?.left) || 0;
      const rightScore = Number(score?.right) || 0;
      if (leftScore > rightScore) {
        winner_id = null; 
        winner_alias = player1_alias;
      } else if (rightScore > leftScore) {
        winner_id = player2_id;
        winner_alias = player2_alias;
      } else {
        winner_id = null;
        winner_alias = null;
      }

      const details = {
        score,
        mode,
        type: "1v1_casual",
      };

      const match = createMatchRecord({
        player1_id,
        player1_alias,
        player2_id,
        player2_alias,
        winner_id,
        winner_alias,
        details,
      });

      return reply.code(201).send(match);
    } catch (err) {
      request.log.error(err);
      return reply.code(500).send({ error: "Failed to save match" });
    }
  });
}
