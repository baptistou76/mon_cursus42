/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:35:04 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 10:45:48 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && (input[i] != '\''))
				i++;
			if (!input[i])
				return (ft_putstr_fd("quote error\n", 2), 1);
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && (input[i] != '\"'))
				i++;
			if (!input[i])
				return (ft_putstr_fd("quote error\n", 2), 1);
		}
		i++;
	}
	return (0);
}

char	*handle_quotes(t_data *data, int *i)
{
	char	*word;

	word = NULL;
	if (data->input[*i] && data->input[*i] == '\"')
		word = extract_word_double(data, i);
	else if (data->input[*i] == '\'')
		word = extract_word_single(data->input, i);
	return (word);
}

char	*handle_quotes_part(t_data *data, int *i, char *value)
{
	char	*tmp;
	char	*temp;

	tmp = handle_quotes(data, i);
	temp = ft_strjoin(value, tmp);
	free(tmp);
	free(value);
	return (temp);
}

t_token	*handle_dollar_quote(t_data *data, int *i)
{
	char	*value;
	t_token	*token;

	(*i)++;
	value = NULL;
	value = handle_quotes_part(data, i, value);
	token = new_token(value, WORD, 1);
	free(value);
	return (token);
}

t_token	*handle_cmd_or_arg(t_data *data, int *i)
{
	char	*value;
	t_token	*token;
	int		quoted;

	if (data->input[*i] == '$' && data->input[*i + 1] == '\"')
		return (handle_dollar_quote(data, i));
	value = NULL;
	quoted = 0;
	while (is_token_char(data->input[*i]))
	{
		if (data->input[*i] == '$')
			value = handle_env_value(data, i, value);
		else
		{
			value = handle_plain_text(data, i, value);
			if (data->input[*i] == '\'' || data->input[*i] == '\"')
			{
				quoted = 1;
				value = handle_quotes_part(data, i, value);
			}
		}
	}
	token = new_token(value, WORD, quoted);
	free(value);
	return (token);
}
