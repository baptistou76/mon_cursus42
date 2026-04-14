import path from 'path';
import fs from 'fs-extra';
import { v4 as uuidv4 } from 'uuid';
import sharp from 'sharp';
import { findUserById, updateUserById, getSessionByJti } from '../db.js';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const UPLOAD_DIR = path.join(process.cwd(), 'uploads', 'avatars');
const MAX_AVATAR_SIZE = 2 * 1024 * 1024; // 2 MB
const VALID_MIME_TYPES = ['image/jpeg', 'image/png', 'image/webp'];

export default async function (fastify, options) {

  fastify.post('/me/avatar', {
    schema: {
      response: {
        200: {
          type: 'object',
          properties: { avatar: { type: 'string' } },
          required: ['avatar']
        }
      }
    }
  }, async (request, reply) => {
	if (!request.user || !request.user.jti) {
      return reply.status(401).send({ error: 'Unauthorized' });
    }
	const session = getSessionByJti(request.user.jti);
	if (!session) {
      return reply.status(401).send({ error: 'Session invalid or expired' });
    }
    const user = findUserById(session.user_id);
    if (!user) {
      return reply.status(404).send({ error: 'User not found' });
    }

    const file = await request.file();
    if (!file) {
      return reply.status(400).send({ error: 'No file uploaded' });
    }

    const fileType = file.mimetype;
    if (!VALID_MIME_TYPES.includes(fileType)) {
      return reply.status(400).send({ error: 'Invalid file type. Use JPEG, PNG, or WEBP formats.' });
    }

    if (file.file.truncated) {
      return reply.status(400).send({ error: 'File size exceeds 2 MB limit.' });
    }

    const chunks = [];
    for await (const chunk of file.file) {
      chunks.push(chunk);
    }

	if (!fs.existsSync(UPLOAD_DIR)){
    	fs.mkdirSync(UPLOAD_DIR, { recursive: true });
}

    const buffer = Buffer.concat(chunks);
    const filename = `${uuidv4()}.webp`;
    const filePath = path.join(UPLOAD_DIR, filename);
    const publicPath = `/uploads/avatars/${filename}`;

    await sharp(buffer)
      .resize(512, 512, {
        fit: 'inside',
      })
      .webp({ quality: 80 })
      .toFile(filePath);

    if (user.avatar) {
      const oldPath = path.join(UPLOAD_DIR, path.basename(user.avatar));
      await fs.remove(oldPath).catch((err) => fastify.log.warn(`Failed to delete old avatar: ${oldPath}`));
    }

    updateUserById(user.id, { avatar: publicPath });

    reply.send({ avatar: publicPath });
  });
  // Update user profile
  fastify.patch('/me', {
    schema: {
      body: {
        type: 'object',
        properties: {
          avatar: { type: 'string', maxLength: 255 },
          displayName: { type: 'string', minLength: 2, maxLength: 64 },
          firstName: { type: 'string', maxLength: 64 },
          lastName: { type: 'string', maxLength: 64 },
          login: { type: 'string', maxLength: 64 }
        },
        additionalProperties: false
      },
      response: {
        200: {
          type: 'object',
          properties: {
            success: { type: 'boolean' },
            updates: { type: 'object' }
          },
          required: ['success','updates']
        }
      }
    }
  }, async (request, reply) => {
	if (!request.user || !request.user.jti) {
      return reply.status(401).send({ error: 'Unauthorized' });
    }

	console.log('PATCH /me - Received Request');
	console.log('Request Body:', request.body);
	console.log('User from JWT:', request.user);

	const session = getSessionByJti(request.user.jti);
    if (!session) {
      return reply.status(401).send({ error: 'Session invalid or expired' });
    }

    const user = findUserById(session.user_id);
    if (!user) {
      return reply.status(404).send({ error: 'User not found' });
    }

    const { avatar, displayName, firstName, lastName, login } = request.body;

    const updates = {};
	if (avatar) updates.avatar = avatar.trim();
    if (displayName) updates.display_name = displayName.trim();
    if (firstName) updates.first_name = firstName.trim();
    if (lastName) updates.last_name = lastName.trim();
    if (login) updates.login = login.trim();

    if (Object.keys(updates).length === 0) {
      return reply.status(400).send({ error: 'No valid fields provided for update.' });
    }

    updateUserById(user.id, updates);

    reply.send({ success: true, updates });
  });
}