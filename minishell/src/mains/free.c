/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:13:11 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:07:26 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_env_list(data->env);
	free_env_list(data->export);
	free(data->input);
	free_token(data->token);
}

void	free_one_token(t_token *token)
{
	if (!token->value)
		return ;
	free(token->value);
	if (!token)
		return ;
	free(token);
}

void	free_token(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head->next;
		if (!head)
			return ;
		free_one_token(head);
		head = tmp;
	}
}

void	free_env_list(t_env *new_list)
{
	t_env	*temp;

	while (new_list)
	{
		temp = new_list;
		new_list = new_list->next;
		free(temp->name);
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->type == HEREDOC && redir->file)
			unlink(redir->file);
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}
