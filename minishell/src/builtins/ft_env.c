/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:30:05 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 19:40:17 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_data *data)
{
	t_env	*i;

	i = data->env;
	while (i)
	{
		ft_printf("%s=%s\n", i->name, i->content);
		i = i->next;
	}
	return (0);
}

void	ft_replace_in_env(t_data *data, char *name, char *value)
{
	t_env	*i;

	i = data->env;
	while (i)
	{
		if (ft_strcmp(i->name, name) == 0)
		{
			free(i->content);
			i->content = ft_strdup(value);
			return ;
		}
		i = i->next;
	}
}

t_env	*env_new(char *name, char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->name = ft_strdup(name);
	if (value)
		new_env->content = ft_strdup(value);
	else
		new_env->content = NULL;
	new_env->next = NULL;
	new_env->prev = NULL;
	return (new_env);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*current;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

char	*handle_env_value(t_data *data, int *i, char *value)
{
	char	*tmp;
	char	*temp;

	if (data->input[*i + 1] == '?')
		return (handle_error_code(data, value, i));
	tmp = change_env(data, i);
	temp = ft_strjoin(value, tmp);
	free(tmp);
	free(value);
	return (temp);
}
