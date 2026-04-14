import db, { blockUser, unblockUser, isUserBlocked, findUserById, getSessionByJti } from '../db.js';
import { getAvatarUrl } from '../utils/avatar.js';

export default async function (fastify, options) {
  fastify.addHook('preHandler', (request, reply, done) => {
    if (!request.user || !request.user.jti) {
      return reply.status(401).send({ error: 'Unauthorized' });
    }
    done();
  });
  // Get list of blocked users
  fastify.get('/me/blocked', async (req, reply) => {
    const session = getSessionByJti(req.user.jti);
    if (!session) {
      return reply.status(401).send({ error: 'Session not found' });
    }
    const userId = session.user_id;

    const rows = db
      .prepare(
        `SELECT b.blocked_id AS id, u.display_name, u.avatar
         FROM blocked_users b
         LEFT JOIN users u ON u.id = b.blocked_id
         WHERE b.user_id = ?`
      )
      .all(userId);

    const rowsWithAvatar = rows.map(row => ({
      ...row,
      avatar: getAvatarUrl(row.avatar)
    }));

    return reply.send(rowsWithAvatar);
  });

  // Block a user by id
  fastify.post('/block/:userId', async (req, reply) => {
    const session = getSessionByJti(req.user.jti);
    if (!session) {
      return reply.status(401).send({ error: 'Session not found' });
    }
    const userId = session.user_id;

    const targetId = Number(req.params.userId);
    if (!Number.isFinite(targetId) || targetId <= 0) {
      return reply.code(400).send({ error: 'Invalid user id' });
    }
    if (targetId === Number(userId)) {
      return reply.code(400).send({ error: 'Cannot block yourself' });
    }

    const target = findUserById(targetId);
    if (!target) return reply.code(404).send({ error: 'User not found' });

    blockUser(Number(userId), targetId);
    return reply.send({ ok: true });
  });

  // Unblock a user by id
  fastify.delete('/block/:userId', async (req, reply) => {
    const session = getSessionByJti(req.user.jti);
    if (!session) {
      return reply.status(401).send({ error: 'Session not found' });
    }
    const userId = session.user_id;

    const targetId = Number(req.params.userId);
    if (!Number.isFinite(targetId) || targetId <= 0) {
      return reply.code(400).send({ error: 'Invalid user id' });
    }

    unblockUser(Number(userId), targetId);
    return reply.send({ ok: true });
  });
}
