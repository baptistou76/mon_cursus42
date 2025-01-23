/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:38:25 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/18 10:52:03 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int     ft_atoi(char *str)
{
        int     i;
        int     sign;
        int     result;

        i = 0;
        sign = 1;
        result = 0;
        while (str[i] && (str[i] == ' '|| str[i] >= 9 && str[i] <= 13))
            i++;
        while (str[i] && (str[i] == '-' || str[i] == '+'))
        {
                if ( str[i] == '-')
                        sign = - 1;
                i++;
         }
        while (str[i] && (str[i] >= '0' && str[i] <= '9'))
        {
            result = result * 10 + (str[i] - '0');
            i++;
        }
        return (sign * result);           
}
/*
int     main(void)
{
    char    test1[] = "\n  \0 --+-++124568Qbfgd21";
    char    test2[] = "   \n  --++--+-jhkwfhwk54682";

    printf("%d\n", ft_atoi(test1));
    printf("%d\n", ft_atoi(test2));
    return (0);
}*/