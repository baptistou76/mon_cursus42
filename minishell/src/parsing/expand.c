/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:43:56 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:19:31 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*append_env_variable(t_data *data, char *extract, int *i, int *first)
{
	int		last;
	char	*teemp;
	char	*tmp;
	char	*temp;

	last = *i;
	teemp = ft_substr(data->input, *first + 1, last - *first - 1);
	tmp = change_env(data, i);
	*first = *i - 1;
	temp = ft_strjoin(teemp, tmp);
	free(teemp);
	free(tmp);
	teemp = ft_strjoin(extract, temp);
	free(temp);
	free(extract);
	return (teemp);
}

char	*append_remaining_segment(t_data *data, char *extract, int first, int i)
{
	char	*tmp;
	char	*temp;

	tmp = ft_substr(data->input, first + 1, i - first - 1);
	temp = ft_strjoin(extract, tmp);
	free(tmp);
	free(extract);
	return (temp);
}

char	*extract_word_double(t_data *data, int *i)
{
	int		first;
	char	*extract;

	extract = NULL;
	first = (*i)++;
	while (data->input[*i] && data->input[*i] != '\"')
	{
		if (data->input[*i] == '$')
		{
			if (data->input[*i + 1] == '?')
				extract = append_error_code(data, extract, i, &first);
			else
				extract = append_env_variable(data, extract, i, &first);
		}
		else
			(*i)++;
	}
	extract = append_remaining_segment(data, extract, first, *i);
	(*i)++;
	return (extract);
}

char	*extract_word_single(char *input, int *i)
{
	int		first;
	int		last;
	char	*extract;

	first = (*i);
	(*i)++;
	while (input[*i] != '\'')
		(*i)++;
	last = (*i);
	extract = ft_substr(input, first + 1, (last - first - 1));
	(*i)++;
	return (extract);
}
