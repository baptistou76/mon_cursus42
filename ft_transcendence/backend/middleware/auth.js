import fp from "fastify-plugin";
import { getSessionByJti, findUserById } from "../db.js";

export default fp(async function (fastify, opts) {
  fastify.decorate("authenticate", async function (request, reply) {
    try {
      const auth = request.headers.authorization;
      if (!auth || !auth.startsWith("Bearer ")) {
        return reply.status(401).send({ error: "Missing Authorization header" });
      }

      const token = auth.slice(7);
      const decoded = fastify.jwt.verify(token);

      const jti = decoded.jti;
      const session = getSessionByJti(jti);
      if (!session || session.revoked) {
        return reply.status(401).send({ error: "Session not found or revoked" });
      }

      const user = findUserById(decoded.sub);
      if (!user) {
        return reply.status(401).send({ error: "User not found" });
      }

      request.user = {
        id: user.id,
        email: user.email,
        first_name: user.first_name,
        last_name: user.last_name,
        display_name: user.display_name,
        avatar: user.avatar,
        jti: jti
      };

      console.log(`Authenticated user: ${user.id}`);
    } catch (err) {
      console.error("Authentication error:", err.message);
      return reply.status(401).send({ error: "Invalid token" });
    }
  });
});