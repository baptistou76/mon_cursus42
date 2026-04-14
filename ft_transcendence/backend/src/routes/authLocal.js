import bcrypt from 'bcryptjs';
import { randomUUID } from 'crypto';
import { findUserByEmail, createUser, findUserByDisplayName, saveSession } from '../db.js';
import { buildCookieOptions } from '../utils/cookieOptions.js';
import { auditAuth } from '../utils/auditLog.js';

export default async function (fastify, options) {

	fastify.post('/register', {
		schema: {
			body: {
				type: 'object',
				required: ['email', 'password', 'display_name'],
				properties: {
					email: { type: 'string', format: 'email', maxLength: 254 },
					password: { type: 'string', minLength: 8, maxLength: 128 },
					display_name: { type: 'string', minLength: 2, maxLength: 64 },
					first_name: { type: 'string', maxLength: 64 },
					last_name: { type: 'string', maxLength: 64 },
					login: { type: 'string', maxLength: 64 }
				}
			}
		}
	}, async (request, reply) => {
		const { email, password, display_name, first_name, last_name, login } = request.body;

		if (!email || !password || !display_name) {
			return reply.status(400).send({ error: 'Email, password, and display name are required' });
		}
		if (findUserByEmail(email)) {
			return reply.status(409).send({ error: 'Email already exists' });
		}
		if (findUserByDisplayName(display_name)) {
			return reply.status(409).send({ error: 'Display name is already taken' });
		}

		const password_hash = bcrypt.hashSync(password, 12);

		const user = createUser({
			email: String(email).trim().toLowerCase(),
			password_hash,
			display_name: String(display_name).trim(),
			first_name: first_name ? String(first_name).trim() : null,
			last_name: last_name ? String(last_name).trim() : null,
			login: login ? String(login).trim() : null,
			created_at: new Date().toISOString()
		});

		auditAuth({
			action: "register",
			user,
			request,
			extra: { "auth.method": "local" }
		});

		const jti = randomUUID();
		const token = fastify.jwt.sign(
			{ jti, display_name: user.display_name },
			{ subject: String(user.id), expiresIn: '7d' }
		);

		saveSession({
			user_id: user.id,
			jti,
			issued_at: new Date().toISOString(),
			expires_at: new Date(Date.now() + 7 * 24 * 3600 * 1000).toISOString()
		});

		const cookieOptions = buildCookieOptions();
		reply
			.setCookie('access_token', token, cookieOptions)
			.status(201)
			.send({ id: user.id, email: user.email, display_name: user.display_name });
	});

	fastify.post('/login', {
		schema: {
			body: {
				type: 'object',
				required: ['email', 'password'],
				properties: {
					email: { type: 'string', format: 'email', maxLength: 254 },
					password: { type: 'string', minLength: 8, maxLength: 128 }
				}
			}
		}
	}, async (request, reply) => {
		const { email, password } = request.body;

		if (!email || !password) {
			return reply.status(400).send({ error: 'Email and password are required' });
		}

		const user = findUserByEmail(String(email).trim().toLowerCase());
		if (!user || !user.password_hash) {
			return reply.status(401).send({ error: 'Invalid credentials' });
		}

		const isPasswordValid = bcrypt.compareSync(password, user.password_hash);
		if (!isPasswordValid) {
			return reply.status(401).send({ error: 'Invalid credentials' });
		}

		auditAuth({
			action: "login",
			user,
			request,
			extra: { "auth.method": "local" }
		});

		const jti = randomUUID();
		const token = fastify.jwt.sign(
			{ jti, display_name: user.display_name },
			{ subject: String(user.id), expiresIn: '7d' }
		);

		saveSession({
			user_id: user.id,
			jti,
			issued_at: new Date().toISOString(),
			expires_at: new Date(Date.now() + 7 * 24 * 3600 * 1000).toISOString()
		});

		const cookieOptions = buildCookieOptions();
		reply
			.setCookie('access_token', token, cookieOptions)
			.send({ message: 'Login successful' });
	});
}
