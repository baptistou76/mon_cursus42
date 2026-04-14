/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:09:16 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/28 20:48:45 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>
# include <stddef.h>

template <typename T, typename F> void iter(T *array, const size_t length,
	F func)
{
	if (!array || length == 0)
		return ;
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

template <typename T, typename F> void iter(const T *array, const size_t length,
	F func)
{
	if (!array || length == 0)
		return ;
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

#endif