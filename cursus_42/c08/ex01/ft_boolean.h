/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_boolean.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:55:26 by bcaumont          #+#    #+#             */
/*   Updated: 2024/07/22 15:43:27 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BOOLEAN_H
# define FT_BOOLEAN_H

# include <unistd.h>
# define TRUE 1
# define FALSE 0
# define EVEN(x) ((x + 1) %2)
# define EVEN_MSG "I have an even number of arguments.\n"
# define ODD_MSG " I have an odd number of argumens.\n"
# define SUCCESS 0

typedef int	t_bool;

#endif
