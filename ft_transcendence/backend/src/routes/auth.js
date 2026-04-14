import { revokeSession, findUserById, getSessionByJti } from "../db.js";
import { auditAuth } from "../utils/auditLog.js";

export default async function (fastify, options) {
fastify.get("/me", async (request, reply) => {
	fastify.log.info("GET /me called");
	if (!request.user || !request.user.jti) {
		fastify.log.warn("Unauthorized access attempt");
		return reply.status(401).send({ error: "Unauthorized" });
  }

  fastify.log.info(`Fetching profile for user with jti: ${request.user.jti}`);
  const session = getSessionByJti(request.user.jti);
  if (!session) {
	fastify.log.warn("Session not found");
    return reply.status(401).send({ error: "Session not found" });
  }

  const user = findUserById(session.user_id);
  if (!user) {
	fastify.log.error(`User not found for session user_id: ${session.user_id}`);
    return reply.status(404).send({ error: "User not found" });
  }

  reply.send({
    id: user.id,
    login: user.display_name,
    email: user.email,
    display_name: user.display_name,
    avatar: user.avatar,
    first_name: user.first_name,
    last_name: user.last_name
  });
});

fastify.post("/logout", async (request, reply) => {
    try {
        const session = request.user?.jti ? getSessionByJti(request.user.jti) : null;
        const user = session ? findUserById(session.user_id) : null;
        auditAuth({
          action: "logout",
          user: user ? { id: user.id, display_name: user.display_name } : { id: Number(request.user?.sub) || null },
          request,
          extra: { "auth.method": "local_or_42" }
        });

        if (request.user && request.user.jti) {
            revokeSession(request.user.jti);
            console.log(`User ${request.user.sub} logged out`);
        }

        reply.clearCookie('access_token', { path: '/' });
        
        reply.send({ success: true, message: "Logged out successfully" });
    } catch (error) {
        console.error("Error in /api/logout:", error);
        reply.clearCookie('access_token', { path: '/' });
        reply.send({ success: true, message: "Logged out" });
    }
});
}
