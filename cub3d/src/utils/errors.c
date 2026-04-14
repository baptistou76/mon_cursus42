/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:44:48 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/21 02:55:17 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Affiche un message d'erreur en rouge dans le terminal
 * @param str message à afficher
 * @param exit_status code de retour
 * @return exit_status (permet d'enchaîner avec un return)
 */
int	print_error(char *str, int exit_status)
{
	ft_putstr_fd("\033[31mError\033[39m\n", 2);
	ft_putstr_fd(str, 2);
	return (exit_status);
}

/**
 * Vérifie si un nom de fichier se termine par ".cub"
 * @param filename nom du fichier à vérifier
 * @return 1 si l’extension est correcte, 0 sinon
 */
int	is_file_extension_correct(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 5)
		return (0);
	if (filename[i - 1] != 'b' || filename[i - 2] != 'u' || filename[i
			- 3] != 'c' || filename[i - 4] != '.')
		return (0);
	return (1);
}
