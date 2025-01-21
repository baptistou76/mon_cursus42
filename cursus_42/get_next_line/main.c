/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:03:11 by bcaumont          #+#    #+#             */
/*   Updated: 2024/11/16 10:21:40 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	int		*fds;
	int		i;
	char	*line;
	int		finished;

	if (argc < 2)
	{
		printf("Usage: %s <Tu_a_oulie_quelque_chose>\n", argv[0]);
		return (1);
	}
	fds = malloc((argc - 1) * sizeof(int));
	if (!fds)
		return (perror("Erreur d'allocation"), 1);
	i = 0;
	while (i < argc - 1)
	{
		fds[i] = open(argv[i + 1], O_RDONLY);
		if (fds[i] == -1)
		{
			perror("Erreur lors de l'ouverture d'un fichier");
			while (i-- > 0)
				close(fds[i]);
			free(fds);
			return (1);
		}
		i++;
	}
	finished = 0;
	while (!finished)
	{
		finished = 1;
		i = 0;
		while (i < argc - 1)
		{
			line = get_next_line(fds[i]);
			if (line)
			{
				printf("Fichier %d: %s\n", i + 1, line);
				free(line);
				finished = 0;
			}
			i++;
		}
	}
	i = 0;
	while (i < argc - 1)
		close(fds[i++]);
	free(fds);
	return (0);
}
