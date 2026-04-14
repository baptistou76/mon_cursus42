import fp from 'fastify-plugin';
import { getSessionByJti, isUserBlocked } from '../db.js';

export default fp(async function (fastify, opts) {

    fastify.get('/ws/chat', { websocket: true }, (connection, req) => {
        const socket = connection?.socket ?? connection;

        const closeUnauthorized = (reason) => {
            fastify.log.warn(reason);
            if (socket && typeof socket.close === 'function') {
                try {
                    socket.close(1008, 'Unauthorized');
                    return;
                } catch (err) {
                    fastify.log.error('WS: Failed to close unauthorized connection', err);
                }
            }
            if (req?.raw?.socket) {
                req.raw.socket.destroy();
            }
        };

        let jti = req.user?.jti;
        if (!jti) {
            try {
                const cookieHeader = req.headers?.cookie || '';
                const cookies = Object.fromEntries(
                    cookieHeader.split(';').map(kv => {
                        const idx = kv.indexOf('=');
                        if (idx === -1) return [kv.trim(), ''];
                        const key = kv.slice(0, idx).trim();
                        const val = decodeURIComponent(kv.slice(idx + 1));
                        return [key, val];
                    })
                );
                const token = cookies['access_token'];
                if (token) {
                    const decoded = fastify.jwt.verify(token);
                    jti = decoded?.jti;
                    req.user = decoded;
                }
            } catch (err) {
                fastify.log.warn('WS: Cookie fallback auth failed:', err?.message || err);
            }
        }
        if (!jti) {
            closeUnauthorized('WS: Missing session token on connection attempt.');
            return;
        }

        const session = getSessionByJti(jti);
        if (!session || session.revoked) {
            closeUnauthorized('WS: Session invalid or revoked.');
            return;
        }

        const userId = Number(session.user_id);
        if (!userId) {
            closeUnauthorized('WS: Invalid user id resolved from session.');
            return;
        }

        fastify.wsManager.addConnection(userId, socket);

        const onlineUsers = fastify.wsManager.getOnlineUsers();
        fastify.log.info(`WS: User ${userId} connected. Sending list of ${onlineUsers.length} online users`);
        onlineUsers.forEach(onlineUserId => {
            fastify.wsManager.sendToUser(userId, {
                type: 'STATUS_UPDATE',
                userId: onlineUserId,
                isOnline: true,
                timestamp: new Date().toISOString()
            });
        });

        const onlineStatus = {
            type: 'STATUS_UPDATE',
            userId: userId,
            isOnline: true,
            timestamp: new Date().toISOString()
        };
        fastify.log.info(`WS: Broadcasting online status for user ${userId}`);
		fastify.wsManager.broadcast(onlineStatus);

        socket.on('message', message => {
            const raw = message.toString();
            let parsed;

            try {
                parsed = JSON.parse(raw);
            } catch (err) {
                fastify.log.warn(`WS: Failed to parse message from ${userId}: ${raw}`);
                return;
            }

            const content = typeof parsed.content === 'string' ? parsed.content.trim() : '';
            if (!content) {
                fastify.log.warn(`WS: Empty message discarded from ${userId}`);
                return;
            }
            if (content.length > 500) {
                fastify.log.warn(`WS: Message too long from ${userId} (len=${content.length})`);
                return;
            }

            fastify.log.info(`WS: Message from ${userId}: ${content}`);

            if (Object.prototype.hasOwnProperty.call(parsed, 'recipientId')) {
                const recipientId = Number(parsed.recipientId);
                if (!Number.isFinite(recipientId) || recipientId <= 0) {
                    fastify.log.warn(`WS: Invalid recipientId from ${userId}: ${parsed.recipientId}`);
                    return;
                }
                try {
                    const blocked = isUserBlocked(recipientId, userId);
                    if (blocked) {
                        fastify.log.info(`WS: Message from ${userId} to ${recipientId} blocked by recipient.`);
                        fastify.wsManager.sendToUser(userId, {
                            type: 'CHAT_BLOCKED',
                            senderId: userId,
                            recipientId,
                            content: 'Message not delivered: recipient has blocked you.',
                            timestamp: new Date().toISOString()
                        });
                        return;
                    }
                } catch (err) {
                    fastify.log.error(`WS: Block check failed: ${err?.message || err}`);
                    return;
                }

                const messageData = {
                    type: parsed.type || 'CHAT_MESSAGE',
                    senderId: userId,
                    recipientId,
                    content,
                    timestamp: parsed.timestamp || new Date().toISOString()
                };
                fastify.wsManager.sendToUser(recipientId, messageData);
                fastify.wsManager.sendToUser(userId, messageData);
            } else {
                fastify.wsManager.broadcast({ 
                    type: parsed.type || 'CHAT_MESSAGE', 
                    senderId: userId, 
                    content,
                    timestamp: parsed.timestamp || new Date().toISOString()
                });
            }
        });
        
        socket.on('close', () => {
            const current = fastify.wsManager.getConnection(userId);
            if (current && current.socket === socket) {
                fastify.wsManager.removeConnection(userId);
                const offlineStatus = {
                    type: 'STATUS_UPDATE',
                    userId: userId,
                    isOnline: false,
                    timestamp: new Date().toISOString()
                };
                fastify.log.info(`WS: Broadcasting offline status for user ${userId}`);
                fastify.wsManager.broadcast(offlineStatus);
            } else {
                fastify.log.info(`WS: Skip offline broadcast for user ${userId} (old socket closed)`);
            }
        });
    });
});