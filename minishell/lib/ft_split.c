/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:56:53 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/03 15:02:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	in_word;
	int	result;

	result = 0;
	in_word = 0;
	while (*str)
	{
		if ((*str != c) && in_word == 0)
		{
			in_word = 1;
			result++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (result);
}

static int	word_lenght(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*free_tab(char **tab, int len_tab)
{
	int	i;

	i = 0;
	if (tab[0] == NULL)
		return (NULL);
	while (i < len_tab)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split_tab;
	int		i;
	char	*new_str;
	int		nb_words;

	nb_words = count_words(s, c);
	split_tab = malloc((nb_words + 1) * sizeof(char *));
	if (split_tab == NULL)
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		while (*s == c)
			s++;
		new_str = ft_substr(s, 0, word_lenght(s, c));
		if (new_str == NULL)
			return (free_tab(split_tab, i));
		split_tab[i] = new_str;
		s += word_lenght(s, c);
		i++;
	}
	split_tab[i] = NULL;
	return (split_tab);
}
