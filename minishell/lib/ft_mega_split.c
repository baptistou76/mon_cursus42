/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mega_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:40 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/12 18:40:20 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_delimiter(char c, const char *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (true);
		delimiters++;
	}
	return (false);
}

static int	count_tokens(const char *str, const char *delimiters)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			in_quotes = !in_quotes;
		if (!in_quotes && !is_delimiter(*str, delimiters) && (is_delimiter(*(str
						+ 1), delimiters) || !*(str + 1)))
			count++;
		str++;
	}
	return (count);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static char	*extract_token(const char **str, const char *delimiters)
{
	const char	*start;
	char		*token;
	int			len;

	while (is_delimiter(**str, delimiters))
		(*str)++;
	start = *str;
	while (**str && !is_delimiter(**str, delimiters))
		(*str)++;
	len = *str - start;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strncpy(token, start, len);
	token[len] = '\0';
	return (token);
}

char	**mega_split(const char *str, const char *delimiters)
{
	char	**tokens;
	int		token_count;
	int		i;

	if (!str || !delimiters)
		return (NULL);
	token_count = count_tokens(str, delimiters);
	tokens = malloc((token_count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		tokens[i] = extract_token(&str, delimiters);
		if (!tokens[i])
		{
			while (i > 0)
				free(tokens[--i]);
			free(tokens);
			return (NULL);
		}
		i++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}
