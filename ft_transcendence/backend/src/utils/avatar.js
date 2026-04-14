const DEFAULT_AVATAR_PATH = '/public/avatar.png';

export function getAvatarUrl(avatar) {
    return avatar || DEFAULT_AVATAR_PATH;
}

export function normalizeUserAvatar(user) {
    if (!user) return null;
    return {
        ...user,
        avatar: getAvatarUrl(user.avatar)
    };
}
