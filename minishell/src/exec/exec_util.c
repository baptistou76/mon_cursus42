/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:17:24 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 15:36:06 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_get_cmd(t_data *data)
{
	t_token	*i;
	char	**cmd;
	int		len;
	int		j;

	len = 0;
	i = data->token;
	while (i && i->type == WORD)
	{
		len++;
		i = i->next;
	}
	cmd = malloc(sizeof(char *) * (len + 1));
	i = data->token;
	j = 0;
	while (i && i->type == WORD)
	{
		cmd[j++] = ft_strdup(i->value);
		i = i->next;
	}
	cmd[j] = NULL;
	return (cmd);
}

int	wait_for_children(t_data *data, pid_t last_pid, int prev_fd)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		safe_close(data->cmd_list->pipe_fd[READ]);
		safe_close(data->cmd_list->pipe_fd[WRITE]);
		safe_close(prev_fd);
		if (wpid == last_pid)
		{
			if (WIFSIGNALED(status))
				data->last_status = 128 + WTERMSIG(status);
			else
				data->last_status = WEXITSTATUS(status);
		}
		wpid = wait(&status);
	}
	return (data->last_status);
}

void	handle_useless_command(t_cmd *cmd, int *prev_fd)
{
	int	tmp_fd;

	if (!cmd->args)
	{
		if (cmd->outfile)
		{
			tmp_fd = last_outfile(cmd);
			if (tmp_fd != -1)
			{
				safe_close(tmp_fd);
				safe_close(*prev_fd);
			}
		}
		if (cmd->infile)
		{
			tmp_fd = last_infile(cmd);
			if (tmp_fd != -1)
			{
				safe_close(*prev_fd);
				safe_close(tmp_fd);
			}
		}
	}
}

void	handle_invalid_command(t_data *data, t_cmd *cmd, int prev_fd)
{
	safe_close(cmd->pipe_fd[READ]);
	safe_close(cmd->pipe_fd[WRITE]);
	safe_close(prev_fd);
	ft_exit_exec(0, data, cmd);
}
