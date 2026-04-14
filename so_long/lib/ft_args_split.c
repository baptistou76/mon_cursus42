/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:04:07 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/12 21:28:42 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static char	*handle_quotes(char *str, int *i, char quote)
{
	int		start;
	char	*result;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == '\0')
		return (NULL);
	result = ft_substr(str, start, *i - start + 1);
	(*i)++;
	return (result);
}

static char	*handle_word(char *str, int *i)
{
	int		start;
	char	*result;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\n'
		&& !is_quote(str[*i]))
		(*i)++;
	result = ft_substr(str, start, *i - start);
	return (result);
}

static char	*handle_token(char *str, int *i)
{
	char	*token;

	if (is_quote(str[*i]))
	{
		token = handle_quotes(str, i, str[*i]);
		if (token == NULL)
			return (NULL);
	}
	else
	{
		token = handle_word(str, i);
		if (token == NULL)
			return (NULL);
	}
	return (token);
}

char	**args_split(char *str)
{
	char	**result;
	int		i;
	int		j;

	result = malloc(sizeof(char *) * 64);
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		else
		{
			result[j] = handle_token(str, &i);
			if (result[j] == NULL)
				return (ft_args_split_free(result));
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
