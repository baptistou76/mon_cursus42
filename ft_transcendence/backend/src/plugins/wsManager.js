import fp from 'fastify-plugin';

async function wsManager(fastify, opts) {
    const activeConnections = new Map();

    function addConnection(userId, socket) {
        if (activeConnections.has(userId)) {
            fastify.log.warn(`WS Manager: Closing old connection for user ${userId}.`);
            activeConnections.get(userId).socket.close(1000, 'New connection established');
        }
        activeConnections.set(userId, { socket, userId });
        fastify.log.info(`WS Manager: User ${userId} connected. Total active: ${activeConnections.size}`);
    }

    function removeConnection(userId) {
        activeConnections.delete(userId);
        fastify.log.info(`WS Manager: User ${userId} disconnected. Total active: ${activeConnections.size}`);
    }

    function sendToUser(userId, payload) {
        const conn = activeConnections.get(userId);
        if (conn && conn.socket.readyState === 1) { // readyState === 1: OPEN
            try {
                conn.socket.send(JSON.stringify(payload));
                return true;
            } catch (error) {
                fastify.log.error(`WS Manager: Failed to send message to ${userId}: ${error.message}`);
                return false;
            }
        }
        fastify.log.info(`WS Manager: User ${userId} is offline or connection closed.`);
        return false;
    }

    function broadcast(payload) {
        const message = JSON.stringify(payload);
        for (const conn of activeConnections.values()) {
            if (conn.socket.readyState === 1) {
                conn.socket.send(message);
            }
        }
    }

    function isUserOnline(userId) {
        const conn = activeConnections.get(userId);
        return !!conn && conn.socket.readyState === 1;
    }
    
    function getConnection(userId) {
        return activeConnections.get(userId) || null;
    }
    
    function getOnlineUsers() {
        return Array.from(activeConnections.keys());
    }

    fastify.decorate('wsManager', {
        addConnection,
        removeConnection,
        sendToUser,
        broadcast,
        isUserOnline,
        getOnlineUsers,
        getConnection
    });

    fastify.addHook('onClose', (instance, done) => {
        fastify.log.info('WS Manager: Closing all connections before server shutdown.');
        for (const conn of activeConnections.values()) {
            if (conn.socket.readyState === 1) {
                conn.socket.close(1001, 'Server closing'); // 1001 - Going Away
            }
        }
        done();
    });
}

export default fp(wsManager);