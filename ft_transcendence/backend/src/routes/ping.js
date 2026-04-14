export default async function (fastify, options) {
  fastify.get('/ping', async (request, reply) => {
    return { pong: 'ok' }
  })
}
