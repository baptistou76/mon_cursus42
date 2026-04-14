/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:46:51 by bcaumont          #+#    #+#             */
/*   Updated: 2025/02/20 10:43:02 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup_here_doc(t_pipex *node)
{
	if (node->infile && ft_strcmp(node->infile, ".here_doc_tmp") == 0)
	{
		if (unlink(".here_doc_tmp") == -1)
			ft_perror(".here_doc: unlink failed");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*node;
	t_data	data;

	if (ac < 5)
		ft_perror("Wrong number of arguments");
	data.av = av;
	data.ac = ac;
	data.envp = envp;
	data.bonus = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		data.bonus = 1;
	node = init_pipeline(&data);
	if (data.bonus)
		here_doc(node);
	process_pipeline(node);
	cleanup_here_doc(node);
	ft_free_pipeline(node);
	return (0);
}
