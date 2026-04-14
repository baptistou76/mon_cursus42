/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:19:33 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/22 11:14:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_pipex *node)
{
	int	tmp_fd;

	tmp_fd = secure_open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC);
	node->infile = ".here_doc_tmp";
	here_doc_put_in(node, tmp_fd);
	secure_close(tmp_fd);
}

void	here_doc_put_in(t_pipex *node, int tmp_fd)
{
	char	*ret;

	ft_putstr_fd("> ", STDOUT_FILENO);
	ret = get_next_line(STDIN_FILENO);
	while (ret && ft_strncmp(ret, node->here_doc, ft_strlen(ret)))
	{
		if (!ret)
			break ;
		if ((ft_strlen(ret) - 1) == ft_strlen(node->here_doc) && ft_strncmp(ret,
				node->here_doc, ft_strlen(node->here_doc)) == 0)
		{
			break ;
		}
		ft_putstr_fd(ret, tmp_fd);
		free(ret);
		ft_putstr_fd("> ", STDOUT_FILENO);
		ret = get_next_line(STDIN_FILENO);
	}
	free(ret);
}
