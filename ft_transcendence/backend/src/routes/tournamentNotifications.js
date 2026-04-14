import { getSessionByJti } from '../db.js';
import { notifyUserTournament, notifyUsersTournament, broadcastTournamentNotification } from '../utils/tournamentNotifications.js';

export default async function tournamentNotificationRoutes(fastify) {
    
    // POST /tournament/notify/me - Send test notification to current user
    fastify.post('/tournament/notify/me', {
        preHandler: fastify.authenticate,
    }, async (req, reply) => {
        const session = getSessionByJti(req.user.jti);
        if (!session) {
            return reply.code(401).send({ error: 'Invalid session' });
        }

        const userId = session.user_id;
        const message = req.body?.message || 'Your tournament match is ready! 🎮';

        const success = notifyUserTournament(fastify, userId, message);
        
        if (success) {
            return { success: true, message: 'Notification sent' };
        } else {
            return reply.code(500).send({ error: 'Failed to send notification' });
        }
    });

    // POST /tournament/notify/user/:userId - Send notification to specific user (admin only for now)
    fastify.post('/tournament/notify/user/:userId', {
        preHandler: fastify.authenticate,
    }, async (req, reply) => {
        const targetUserId = parseInt(req.params.userId, 10);
        if (isNaN(targetUserId)) {
            return reply.code(400).send({ error: 'Invalid user ID' });
        }

        const message = req.body?.message || 'Tournament notification';
        
        const success = notifyUserTournament(fastify, targetUserId, message);
        
        if (success) {
            return { success: true, message: 'Notification sent to user ' + targetUserId };
        } else {
            return reply.code(500).send({ error: 'Failed to send notification' });
        }
    });

    // POST /tournament/notify/broadcast - Broadcast notification to all online users
    fastify.post('/tournament/notify/broadcast', {
        preHandler: fastify.authenticate,
    }, async (req, reply) => {
        const message = req.body?.message || 'Tournament announcement!';
        
        const success = broadcastTournamentNotification(fastify, message);
        
        if (success) {
            const onlineCount = fastify.wsManager.getOnlineUsers().length;
            return { 
                success: true, 
                message: `Notification broadcast to ${onlineCount} online users` 
            };
        } else {
            return reply.code(500).send({ error: 'Failed to broadcast notification' });
        }
    });

    // POST /tournament/notify/users - Notify multiple users
    fastify.post('/tournament/notify/users', {
        preHandler: fastify.authenticate,
        schema: {
            body: {
                type: 'object',
                required: ['userIds', 'message'],
                properties: {
                    userIds: { type: 'array', items: { type: 'number' } },
                    message: { type: 'string' }
                }
            }
        }
    }, async (req, reply) => {
        const { userIds, message } = req.body;

        if (!Array.isArray(userIds) || userIds.length === 0) {
            return reply.code(400).send({ error: 'userIds must be a non-empty array' });
        }

        const successCount = notifyUsersTournament(fastify, userIds, message);
        
        return { 
            success: true, 
            message: `Notification sent to ${successCount}/${userIds.length} users` 
        };
    });
}
