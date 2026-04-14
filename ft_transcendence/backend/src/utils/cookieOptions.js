const DEFAULT_MAX_AGE_SECONDS = 7 * 24 * 60 * 60; // 7 days

const ensureBoolean = (value, fallback) => {
  if (value === undefined) return fallback;
  return value === 'true';
};

export const buildCookieOptions = () => {
  const maxAgeEnv = process.env.COOKIE_MAX_AGE;
  const maxAge = maxAgeEnv ? Number(maxAgeEnv) : DEFAULT_MAX_AGE_SECONDS;
  const secure = ensureBoolean(process.env.COOKIE_SECURE, process.env.NODE_ENV === 'production');
  const sameSite = process.env.COOKIE_SAMESITE || 'lax';
  const domain = process.env.COOKIE_DOMAIN?.trim();

  const options = {
    httpOnly: true,
    secure,
    sameSite,
    path: '/',
    maxAge,
  };

  if (domain) {
    options.domain = domain;
  }

  return options;
};
