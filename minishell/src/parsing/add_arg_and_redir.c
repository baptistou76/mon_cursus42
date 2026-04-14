/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg_and_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:09:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 10:29:58 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	char	**new_args;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			new_args[i] = ft_strdup(cmd->args[i]);
			i++;
		}
		free_split(cmd->args);
	}
	new_args[i++] = ft_strdup(value);
	new_args[i] = NULL;
	cmd->args = new_args;
}

int	add_redir(t_redir **redir_list, char *filename, int type,
		int *skip_next_word)
{
	t_redir	*new_node;
	t_redir	*tmp;

	*skip_next_word = 1;
	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (1);
	if (type == HEREDOC)
		new_node->file = get_here_doc(filename);
	else
		new_node->file = ft_strdup(filename);
	if (!new_node->file)
		return (free(new_node), -1);
	new_node->type = type;
	new_node->next = NULL;
	if (*redir_list == NULL)
		*redir_list = new_node;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (0);
}

int	redir_assigment(t_cmd *curr, t_token *token, int *skip_next_word)
{
	int	ret;

	ret = 0;
	if (!token->next)
		return (0);
	*skip_next_word = 1;
	if (token->type == REDIRECTION_IN)
		ret = add_redir(&curr->infile, token->next->value, REDIRECTION_IN,
				skip_next_word);
	else if (token->type == REDIRECTION_OUT)
		ret = add_redir(&curr->outfile, token->next->value, REDIRECTION_OUT,
				skip_next_word);
	else if (token->type == APPEND)
		ret = add_redir(&curr->outfile, token->next->value, APPEND,
				skip_next_word);
	else if (token->type == HEREDOC)
		ret = add_redir(&curr->infile, token->next->value, HEREDOC,
				skip_next_word);
	return (ret);
}

t_token	*redir_token(char *input, int *i)
{
	int		count;
	char	type;

	count = 0;
	type = input[*i];
	while (input[*i + count] == type)
		count++;
	if (count > 2)
		return (printf("%s '%c%c'\n", ERR_SYNT, type, type), NULL);
	if (count == 2)
	{
		if (type == '>')
			return (*i += 2, new_token(">>", APPEND, 0));
		else if (type == '<')
			return (*i += 2, new_token("<<", HEREDOC, 0));
	}
	else if (count == 1)
	{
		if (type == '>')
			return (*i += 1, new_token(">", REDIRECTION_OUT, 0));
		else if (type == '<')
			return (*i += 1, new_token("<", REDIRECTION_IN, 0));
	}
	return (NULL);
}

t_token	*redir_double(char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		if (input[*i + 2] == '>')
		{
			ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
			return (NULL);
		}
		(*i) += 2;
		return (new_token(">>", APPEND, 0));
	}
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		if (input[*i + 2] == '<')
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (NULL);
		}
		(*i) += 2;
		return (new_token("<<", HEREDOC, 0));
	}
	return (NULL);
}
