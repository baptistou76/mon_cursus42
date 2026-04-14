import { findUserById, searchUsersByDisplayName, getSessionByJti, getUserMatchStats, getUserRecentMatches, getUserMatchesCount } from "../db.js";
import { getAvatarUrl } from "../utils/avatar.js";

export default async function (fastify, options) {

	fastify.get('/users/me', async (request, reply) => {
		await fastify.authenticate(request, reply);
		const user = await findUserById(request.user.id);
		if (!user) {
			return reply.status(404).send({ error: "User not found" });
		}
		
		return {
			id: user.id,
			email: user.email,
			first_name: user.first_name,
			last_name: user.last_name,
			display_name: user.display_name,
			avatar: getAvatarUrl(user.avatar)
		}
	});

	// Get list of currently online user IDs
	// GET /users/online
	fastify.get('/users/online', {
		schema: {
			response: {
				200: {
					type: 'object',
					properties: { online: { type: 'array', items: { type: 'number' } } },
					required: ['online']
				}
			}
		}
	}, async (request, reply) => {
		if (!request.user || !request.user.jti) {
			return reply.status(401).send({ error: 'Unauthorized' });
		}

		try {
			const onlineUserIds = fastify.wsManager.getOnlineUsers();
			return { online: onlineUserIds };
		} catch (error) {
			fastify.log.error('Error getting online users:', error);
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	// Search users by display_name (partial match)
	// GET /users?search=name
	fastify.get('/users', {
		schema: {
			querystring: {
				type: 'object',
				properties: { search: { type: 'string', minLength: 2, maxLength: 64 } },
				required: ['search']
			},
			response: {
				200: {
					type: 'array',
					items: {
						type: 'object',
						properties: {
							id: { type: 'number' },
							display_name: { type: 'string' },
							avatar: { type: 'string' },
							is_online: { type: 'boolean' }
						},
						required: ['id','display_name','is_online']
					}
				}
			}
		}
	}, async (request, reply) => {
		if (!request.user || !request.user.jti) {
			return reply.status(401).send({ error: 'Unauthorized' });
		}

		const { search } = request.query;
		
		if (!search || typeof search !== 'string' || search.trim().length === 0) {
			return reply.status(400).send({ error: 'Search parameter is required' });
		}

		const searchTerm = search.trim();
		
		if (searchTerm.length < 2) {
			return reply.status(400).send({ error: 'Search term must be at least 2 characters' });
		}

		try {
			const users = searchUsersByDisplayName(searchTerm);

			const usersWithStatus = users.map(user => ({
				id: user.id,
				display_name: user.display_name,
				avatar: getAvatarUrl(user.avatar),
				is_online: fastify.wsManager.isUserOnline(user.id)
			}));

			const session = getSessionByJti(request.user.jti);
			const currentUserId = session.user_id;
			const filteredUsers = usersWithStatus.filter(u => u.id !== currentUserId);

			return filteredUsers;
		} catch (error) {
			fastify.log.error('Error searching users:', error);
			return reply.status(500).send({ error: 'Internal server error' });
		}
	});

	// GET /users/:userId - Get user profile (public info)
	fastify.get('/users/:userId', async (request, reply) => {
		const userId = parseInt(request.params.userId, 10);
		if (isNaN(userId)) {
			return reply.code(400).send({ error: "Invalid user ID" });
		}

		const user = findUserById(userId);
		if (!user) {
			return reply.code(404).send({ error: "User not found" });
		}

		return {
			id: user.id,
			display_name: user.display_name,
			avatar: getAvatarUrl(user.avatar),
			login: user.login,
		};
	});

	// GET /users/:userId/stats - Get user match stats
	fastify.get('/users/:userId/stats', async (request, reply) => {
		const userId = parseInt(request.params.userId, 10);
		if (isNaN(userId)) {
			return reply.code(400).send({ error: "Invalid user ID" });
		}

		const user = findUserById(userId);
		if (!user) {
			return reply.code(404).send({ error: "User not found" });
		}

		const stats = getUserMatchStats(userId);
		return stats;
	});

	// GET /users/:userId/history - Get user match history with pagination
	fastify.get('/users/:userId/history', async (request, reply) => {
		const userId = parseInt(request.params.userId, 10);
		if (isNaN(userId)) {
			return reply.code(400).send({ error: "Invalid user ID" });
		}

		const user = findUserById(userId);
		if (!user) {
			return reply.code(404).send({ error: "User not found" });
		}

		const limit = parseInt(request.query.limit, 10) || 10;
		const page = parseInt(request.query.page, 10) || 1;
		const offset = (page - 1) * limit;
		
		const total = getUserMatchesCount(userId);
		const totalPages = Math.ceil(total / limit);
		const matches = getUserRecentMatches(userId, limit, offset);

		const enriched = matches.map((m) => {
			const isPlayer1 = m.player1_id === userId;
			const opponentId = isPlayer1 ? m.player2_id : m.player1_id;
			const fallbackAlias = isPlayer1 ? m.player2_alias : m.player1_alias;
			const opponent = opponentId ? findUserById(opponentId) : { id: null, display_name: fallbackAlias, avatar: null };
			let result = "draw";
			if (m.winner_id === userId) result = "win";
			else if (m.winner_id && m.winner_id !== userId) result = "loss";
			else if (!m.winner_id && m.winner_alias) result = "loss";

			return {
				id: m.id,
				played_at: m.played_at ? m.played_at + 'Z' : null,
				player1_id: m.player1_id,
				player2_id: m.player2_id,
				winner_id: m.winner_id,
				result,
				opponent: {
					id: opponent ? opponent.id : null,
					display_name: opponent ? opponent.display_name : fallbackAlias,
					avatar: getAvatarUrl(opponent ? opponent.avatar : null),
				},
				details: m.details,
			};
		});

		return {
			matches: enriched,
			total,
			page,
			limit,
			totalPages
		};
	});
}