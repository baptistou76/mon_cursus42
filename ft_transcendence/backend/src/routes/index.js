export default async function (fastify, options) {
	fastify.get('/', async (request, replay) =>{
		return {
			message: 'API is working',
			school: '42'
		}
	})

}