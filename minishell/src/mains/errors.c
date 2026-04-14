/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:17:45 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:02:35 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_error_code(t_data *data, char *value, int *i)
{
	char	*tmp;
	char	*temp;

	(void)data;
	(*i) += 2;
	tmp = ft_itoa(data->last_status);
	temp = ft_strjoin(value, tmp);
	free(tmp);
	if (value)
		free(value);
	value = temp;
	return (value);
}

char	*append_error_code(t_data *data, char *extract, int *i, int *first)
{
	int		last;
	char	*tmp;
	char	*temp;

	last = *i;
	tmp = ft_substr(data->input, *first + 1, last - *first - 1);
	temp = ft_strjoin(extract, tmp);
	free(tmp);
	free(extract);
	extract = handle_error_code(data, temp, i);
	*first = *i - 1;
	return (extract);
}
