/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:55:53 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/19 21:37:31 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Retourne la longueur de la chaîne sans inclure le caractère '\n'
 * @param str chaîne de caractères
 * @return longueur sans le '\n'
 */
unsigned int	strlen_without_nl(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

/**
 * Duplique une chaîne sans les espaces finaux ni le caractère '\n'
 * @param str chaîne de base
 * @return chaîne allouée nettoyée
 */
char	*strdup_trimmed(const char *str)
{
	char			*result;
	unsigned int	i;
	unsigned int	len;

	len = strlen_without_nl(str);
	if (len == 1 && str[0] == '\n')
		return (ft_strdup(""));
	while (str[len] == '\0' || str[len] == '\n' || str[len] == ' ')
		len--;
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/**
 * Calcule la longueur d'un tableau de chaînes null-terminé
 * @param array tableau de chaînes
 * @return nombre de lignes
 */
int	string_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
