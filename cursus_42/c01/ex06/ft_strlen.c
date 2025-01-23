/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:53:52 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/07 18:54:13 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	count;
	
	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return count;
}
/*
#include <stdio.h>
int	main(void)
{
	char	ch[] = "chainedecharacteres";
	
	ft_strlen(ch);
	printf("%d", ft_strlen(ch));
	return(0);
}
*/
