/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:51:00 by broboeuf          #+#    #+#             */
/*   Updated: 2024/10/25 14:23:48 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		buf_size;

	buf_size = ft_strlen(s) + 1;
	str = malloc(buf_size);
	if (NULL == str)
		return (NULL);
	ft_strlcpy(str, s, buf_size);
	return (str);
}
/*
int	main(int argc, char **argv)
{
    if (argc != 2) 
	{
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *original = argv[1];
    char *duplicate = ft_strdup(original);

    if (duplicate == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Original string: %s\n", original);
    printf("Duplicated string: %s\n", duplicate);
    printf("Length of original string: %zu\n", ft_strlen(original));
    printf("Length of duplicated string: %zu\n", ft_strlen(duplicate));

    free(duplicate);
    return 0;
}
*/