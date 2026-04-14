/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:22:31 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 19:39:06 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse(t_data *data)
{
	t_token	*token;

	if (!data->input)
		return (1);
	data->token = ft_lexer(data);
	if (!data->token)
		return (1);
	if (valid_parse(data) == 1)
		return (1);
	token = data->token;
	if (token->type == PIPE)
		return (printf("%s `|'\n", ERR_SYNT), 1);
	while (token && token->next)
		token = token->next;
	if (token->type == PIPE)
		return (g_status = 2, printf("%s `|'\n", ERR_SYNT), 1);
	data->cmd_list = parse_tokens(data);
	if (!data->cmd_list)
		return (1);
	if (!data->cmd_list->args && !data->cmd_list->outfile
		&& !data->cmd_list->infile)
		return (1);
	return (0);
}

t_cmd	*parse_tokens(t_data *data)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_token	*token;
	int		skip_next_word;

	head = NULL;
	curr = NULL;
	token = data->token;
	skip_next_word = 0;
	if (loop_parse(token, &curr, &head, &skip_next_word) < 0)
		return (NULL);
	return (head);
}

int	loop_parse(t_token *token, t_cmd **curr, t_cmd **head, int *skip_next_word)
{
	int	ret;

	ret = 0;
	while (token)
	{
		if (!*curr)
		{
			*curr = new_cmd_node();
			if (!*head)
				*head = *curr;
		}
		if (*skip_next_word)
		{
			*skip_next_word = 0;
			token = token->next;
			continue ;
		}
		ret = create_parse(token, curr, skip_next_word);
		if (ret < 0)
			return (free_cmd_list2(*head), -1);
		token = token->next;
	}
	return (ret);
}

int	create_parse(t_token *token, t_cmd **curr, int *skip_next_word)
{
	int	ret;

	ret = 0;
	if (token->type == WORD)
		add_arg(*curr, token->value);
	else if (token->type == PIPE)
	{
		(*curr)->next = new_cmd_node();
		(*curr) = (*curr)->next;
	}
	else
	{
		ret = redir_assigment(*curr, token, skip_next_word);
		if (ret == -1)
			return (-1);
	}
	return (ret);
}

int	valid_parse(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type != WORD && !tmp->next && tmp->type != PIPE)
		{
			g_status = 2;
			return (printf("%s `newline`\n", ERR_SYNT), 1);
		}
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
		{
			g_status = 2;
			return (printf("%s `|`\n", ERR_SYNT), 1);
		}
		if ((tmp->type != WORD && tmp->type != PIPE) && (tmp->next
				&& tmp->next->type != WORD))
		{
			g_status = 2;
			return (printf("%s `%s`\n", ERR_SYNT, tmp->next->value), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
