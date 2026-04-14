export function notifyUserTournament(fastify, userId, message) {
    if (!fastify.wsManager) {
        fastify.log.error('WS Manager not available for tournament notification');
        return false;
    }

    const notification = {
        type: 'TOURNAMENT_NOTIF',
        content: message,
        timestamp: new Date().toISOString(),
    };

    try {
        fastify.wsManager.sendToUser(userId, notification);
        fastify.log.info(`Tournament notification sent to user ${userId}: ${message}`);
        return true;
    } catch (err) {
        fastify.log.error(`Failed to send tournament notification to user ${userId}:`, err);
        return false;
    }
}

export function notifyUsersTournament(fastify, userIds, message) {
    if (!Array.isArray(userIds)) {
        fastify.log.warn('notifyUsersTournament: userIds must be an array');
        return;
    }

    let successCount = 0;
    userIds.forEach(userId => {
        if (notifyUserTournament(fastify, userId, message)) {
            successCount++;
        }
    });

    fastify.log.info(`Tournament notification sent to ${successCount}/${userIds.length} users`);
    return successCount;
}

export function broadcastTournamentNotification(fastify, message) {
    if (!fastify.wsManager) {
        fastify.log.error('WS Manager not available for tournament broadcast');
        return false;
    }

    const notification = {
        type: 'TOURNAMENT_NOTIF',
        content: message,
        timestamp: new Date().toISOString(),
    };

    try {
        fastify.wsManager.broadcast(notification);
        const onlineCount = fastify.wsManager.getOnlineUsers().length;
        fastify.log.info(`Tournament broadcast sent to ${onlineCount} online users: ${message}`);
        return true;
    } catch (err) {
        fastify.log.error('Failed to broadcast tournament notification:', err);
        return false;
    }
}

// Example usage in tournament system:
// import { notifyUserTournament, notifyUsersTournament, broadcastTournamentNotification } from './utils/tournamentNotifications.js';
//
// // Notify single user
// notifyUserTournament(fastify, userId, 'Your match starts in 5 minutes!');
//
// // Notify multiple users (e.g., tournament participants)
// notifyUsersTournament(fastify, [userId1, userId2], 'Tournament round 2 is starting!');
//
// // Broadcast to all online users
// broadcastTournamentNotification(fastify, 'New tournament "Summer Cup" has started!');
