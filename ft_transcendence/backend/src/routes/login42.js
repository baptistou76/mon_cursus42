import path from 'path';
import { upsertUserByEmail, saveSession } from '../db.js';
import { randomUUID } from 'crypto';
import { buildCookieOptions } from '../utils/cookieOptions.js';
import { auditAuth } from '../utils/auditLog.js';

export default async function (fastify, options) {
	fastify.get('/login42', async (request, reply) =>{
		console.log("=== /login42 route handler called ===");
		console.log("Request user:", request.user);
		const url = new URL("https://api.intra.42.fr/oauth/authorize");
		url.searchParams.set("client_id", process.env.FORTYTWO_CLIENT_ID);
		url.searchParams.set("redirect_uri", process.env.FORTYTWO_REDIRECT_URI);
		url.searchParams.set("response_type", "code");
		console.log("Redirecting to:", url.toString());
		reply.redirect(url.toString());
	})

	fastify.get('/auth/42/callback', async (request, reply) => {
		try{
		const code = request.query.code;
		if (!code) {
			return reply.status(400).send({ error: "Missing code parameter" });
		}
		const tokenRes = await fetch("https://api.intra.42.fr/oauth/token", {
			method: "POST",
			headers: { "Content-Type": "application/json" },
			body: JSON.stringify({
			grant_type: "authorization_code",
			client_id: process.env.FORTYTWO_CLIENT_ID,
			client_secret: process.env.FORTYTWO_CLIENT_SECRET,
			code,
			redirect_uri: process.env.FORTYTWO_REDIRECT_URI
		})
		});

		const tokenData = await tokenRes.json();
		if (tokenData.error) {
			return reply.status(400).send({ error: "Failed to obtain access token", details: tokenData.error_description });
		}

		const accessToken = tokenData.access_token;

		const userResponse = await fetch("https://api.intra.42.fr/v2/me", {
			headers: { "Authorization": `Bearer ${accessToken}` }
		});
		const userData = await userResponse.json();

		const user = upsertUserByEmail({
			email: userData.email,
			first_name: userData.first_name,
			last_name: userData.last_name,
			display_name: userData.login,
			avatar: userData.image.link || null,
			created_at: new Date().toISOString()
	});

	const jti = randomUUID();
	const issuedAt = new Date().toISOString();
	const expiresAt = new Date(Date.now() + 1000 * 60 * 60 * 24).toISOString();

		const token = fastify.jwt.sign(
			{ jti },
			{ subject: String(user.id), expiresIn: '7d' },
		);

		saveSession({
			user_id: user.id,
			jti,
			issued_at: issuedAt,
			expires_at: expiresAt
		});

		auditAuth({
			action: "login_42",
        	user: { id: user.id, display_name: user.display_name },
        	request,
        	extra: { "auth.provider": "42", "auth.method": "oauth2" }
		});

      const frontend = process.env.FRONTEND_URL;
	  const cookieOptions = buildCookieOptions();
	  reply
	  .setCookie("access_token", token, cookieOptions)
	  .redirect(frontend);
    } catch (error) {
      console.error("OAuth callback error:", error);
      return reply.status(500).send({ error: `Authentication failed: ${error.message}` });
	}
});
}
