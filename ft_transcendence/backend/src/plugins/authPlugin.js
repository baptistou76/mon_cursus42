import fastifyJwt from '@fastify/jwt';
import fastifyCookie from '@fastify/cookie';
import fastifyCors from '@fastify/cors';
import fp from 'fastify-plugin';
import { getSessionByJti } from '../db.js';

async function authPlugin(fastify, options) {
  await fastify.register(fastifyJwt, {
    secret: process.env.JWT_SECRET || 'superjwtsecret',
  });
  await fastify.register(fastifyCookie, {
    secret: process.env.COOKIE_SECRET || 'supersecret',
    hook: 'onRequest',
  });
  await fastify.register(fastifyCors, {
    origin: process.env.FRONTEND_URL,
    credentials: true,
  });

fastify.addHook('onRequest', async (request, reply) => {
    try {
        const token = request.cookies?.access_token;
        if (!token) {
            request.user = null;
            return;
        }
        const decoded = fastify.jwt.verify(token);
        const session = await getSessionByJti(decoded.jti);
        if (!session || session.revoked) {
            throw new Error('Session invalid');
        }
        request.user = decoded;
    } catch (err) {
        request.user = null;
    }
});
}
export default fp(authPlugin); 
