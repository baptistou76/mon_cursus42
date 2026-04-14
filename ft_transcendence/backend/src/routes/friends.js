// backend/src/routes/friends.js

import { findUserById, getFriendsOfUser, addFriend, removeFriend, getSessionByJti } from '../db.js';
import { getAvatarUrl } from '../utils/avatar.js';

export default async function (fastify, options) {
    fastify.addHook('preHandler', (request, reply, done) => {
        if (!request.user || !request.user.jti) {
            return reply.status(401).send({ error: 'Unauthorized' });
        }
        done();
    });

    fastify.get('/friends', async (request, reply) => {
        const session = getSessionByJti(request.user.jti);
        if (!session) {
            return reply.status(401).send({ error: 'Session not found' });
        }
        const userId = session.user_id;
        
        const friends = getFriendsOfUser(userId);

        const friendsWithStatus = friends.map(friend => ({
            ...friend,
            avatar: getAvatarUrl(friend.avatar),
            is_online: fastify.wsManager.isUserOnline(friend.id) 
        }));

        return friendsWithStatus;
    });

    fastify.post('/friends/:friendId', {
        schema: {
            params: {
                type: 'object',
                properties: { friendId: { type: 'string', pattern: '^[0-9]+$' } },
                required: ['friendId']
            }
        }
    }, async (request, reply) => {
        const session = getSessionByJti(request.user.jti);
        if (!session) {
            return reply.status(401).send({ error: 'Session not found' });
        }
        const userId = session.user_id;
        const friendId = Number(request.params.friendId);
        
        if (userId === friendId) {
            return reply.status(400).send({ error: 'Cannot add yourself as a friend' });
        }
        if (!findUserById(friendId)) {
            return reply.status(404).send({ error: 'Friend not found' });
        }

        addFriend(userId, friendId); 
        addFriend(friendId, userId); 

        if (fastify.wsManager.isUserOnline(friendId)) {
            fastify.wsManager.sendToUser(friendId, {
                type: 'FRIEND_UPDATE',
                content: `User ${userId} added you as a friend.`,
                senderId: userId
            });
        }

        return reply.status(201).send({ success: true, message: 'Friend added successfully' });
    });

    fastify.delete('/friends/:friendId', {
        schema: {
            params: {
                type: 'object',
                properties: { friendId: { type: 'string', pattern: '^[0-9]+$' } },
                required: ['friendId']
            }
        }
    }, async (request, reply) => {
        const session = getSessionByJti(request.user.jti);
        if (!session) {
            return reply.status(401).send({ error: 'Session not found' });
        }
        const userId = session.user_id;
        const friendId = Number(request.params.friendId);

        removeFriend(userId, friendId);
        removeFriend(friendId, userId); 

        return reply.status(200).send({ success: true, message: 'Friend removed successfully' });
    });
};