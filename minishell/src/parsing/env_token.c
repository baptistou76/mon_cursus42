/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:46:15 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:18:31 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env(char *str, t_data *data)
{
	t_env	*current;
	char	*value;

	current = data->env;
	while (current)
	{
		if (ft_strcmp(str, current->name) == 0)
		{
			value = ft_strdup(current->content);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}

char	*change_env(t_data *data, int *i)
{
	int		first;
	int		last;
	char	*name;
	char	*value;

	(*i)++;
	first = (*i);
	while (ft_isalnum(data->input[*i]) || data->input[*i] == '_')
		(*i)++;
	last = (*i);
	name = ft_substr(data->input, first, last - first);
	if (!name[0])
		return (free(name), ft_strdup("$"));
	value = ft_get_env(name, data);
	free(name);
	return (value);
}
