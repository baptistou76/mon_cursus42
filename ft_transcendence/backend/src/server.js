import Fastify from 'fastify'
import authPlugin from './plugins/authPlugin.js'
import auth42Login from './routes/login42.js'
import { fileURLToPath } from 'url'
import { dirname, join } from 'path'
import indexRoutes from './routes/index.js'
import pingRoutes from './routes/ping.js'
import userRoutes from './routes/users.js'
import authRoutes from './routes/auth.js'
import authLocalRoutes from './routes/authLocal.js'
import profileRoutes from './routes/profile.js'
import multipart from '@fastify/multipart'
import fastifyStatic from '@fastify/static'
import FastifyWebsocket from '@fastify/websocket'
import wsManagerPlugin from './plugins/wsManager.js'
import ChatWsRoutes from './routes/chatWs.js'
import friendsRoutes from './routes/friends.js'
import statsRoutes from './routes/stats.js'
import blockRoutes from './routes/block.js'
import tournamentNotificationRoutes from './routes/tournamentNotifications.js'
import tournamentsRoutes from './routes/tournaments.js'
import matchesRoutes from './routes/matches.js'
import client from 'prom-client'

const __filename = fileURLToPath(import.meta.url)
const __dirname = dirname(__filename)

const fastify = Fastify({
  logger: true
})

// ===== GRAFANA PARAMETERS =====

client.collectDefaultMetrics()

fastify.get('/metrics', async (req, reply) => {
  reply
    .header('Content-Type', client.register.contentType)
    .send(await client.register.metrics())
})

const containersActive = new client.Gauge({
  name: 'ft_transcendence_containers_active',
  help: 'Number of active containers for ft_transcendence project'
});  

const backendActive = new client.Gauge({
  name: 'backend_active',
  help: 'Backend container running'
});
const frontendActive = new client.Gauge({
  name: 'frontend_active',
  help: 'Frontend container running'
});
const nginxActive = new client.Gauge({
  name: 'nginx_active',
  help: 'Nginx container running'
});

setInterval(() => {
  const totalContainers = 5; 
  containersActive.set(totalContainers);
  backendActive.set(1);
  frontendActive.set(1);
  nginxActive.set(1);
}, 5000);

// ==============================

await fastify.register(multipart, {
    limits: {
        fileSize: 5 * 1024 * 1024, 
    }
});

// Serve static files from public directory
await fastify.register(fastifyStatic, {
  root: join(__dirname, '..', 'public'),
  prefix: '/public/',
});

// Serve uploaded avatars
await fastify.register(fastifyStatic, {
  root: join(process.cwd(), 'uploads'),
  prefix: '/uploads/',
  decorateReply: false
});

await fastify.register(FastifyWebsocket)
await fastify.register(wsManagerPlugin);
await fastify.register(authPlugin)
// Public routes (no authentication required)
fastify.register(auth42Login)
fastify.register(authLocalRoutes, { prefix: '/auth/local' })
fastify.register(indexRoutes)
fastify.register(pingRoutes)
// Protected routes (require authentication)
fastify.register(authRoutes)
fastify.register(profileRoutes)
fastify.register(userRoutes)
fastify.register(friendsRoutes)
fastify.register(statsRoutes)
fastify.register(blockRoutes)
fastify.register(tournamentNotificationRoutes)
fastify.register(ChatWsRoutes)
fastify.register(tournamentsRoutes)
fastify.register(matchesRoutes)


try {
  await fastify.listen({ port: 3000, host: '0.0.0.0' })
  console.log(`Server listening on ${fastify.server.address().port}`)
  console.log(fastify.printRoutes());

} catch (err) {
  fastify.log.error(err)
  process.exit(1)
}
