/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:17:48 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 13:08:32 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
/*
int     main(void)
{
        for (int i = 0; i <= 127; i++)
                if (ft_isdigit(i))
                        printf("%c is adigit\n", i);
}
*/