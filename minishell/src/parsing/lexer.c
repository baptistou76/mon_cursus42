/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:07:07 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 18:29:26 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_lexer(t_data *data)
{
	int		i;
	t_token	*head;
	t_token	*last;
	t_token	*current;
	char	*trimmed;

	trimmed = NULL;
	i = 0;
	head = NULL;
	last = NULL;
	while (data->input[i])
	{
		skip_whitespace(data->input, &i);
		if (!data->input[i])
			break ;
		current = get_next_token(data, &i);
		if (!current)
			return (free_token(head), NULL);
		current = check_token_number(current, trimmed);
		if (!current)
			return (free_token(head), NULL);
		add_token_to_list(&head, &last, current);
	}
	return (head);
}

t_token	*get_next_token(t_data *data, int *i)
{
	if (data->input[*i] == '>' || data->input[*i] == '<')
		return (redir_token(data->input, i));
	if (data->input[*i] == '|')
		return (handle_pipe(i));
	return (handle_cmd_or_arg(data, i));
}

void	add_token_to_list(t_token **head, t_token **last, t_token *new_token)
{
	if (!*head)
		*head = new_token;
	else
		(*last)->next = new_token;
	*last = new_token;
}

char	*handle_plain_text(t_data *data, int *i, char *value)
{
	int		start;
	int		len;
	char	*tmp;
	char	*temp;

	start = *i;
	while (is_skippable_char(data->input[*i]))
		(*i)++;
	len = *i - start;
	tmp = ft_substr(data->input, start, len);
	temp = ft_strjoin(value, tmp);
	free(tmp);
	free(value);
	return (temp);
}

t_token	*handle_pipe(int *i)
{
	char	*value;
	t_token	*token;

	value = ft_strdup("|");
	if (!value)
		return (NULL);
	token = new_token(value, PIPE, 0);
	(*i)++;
	free(value);
	return (token);
}
