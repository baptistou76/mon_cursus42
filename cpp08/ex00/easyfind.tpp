/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:28:19 by bcaumont          #+#    #+#             */
/*   Updated: 2025/10/29 14:25:36 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

template <typename T> typename T::iterator easyfind(T &container, int value)
{
	typename T::iterator it = std::find(container.begin(), container.end(),
			value);
	if (it == container.end())
		throw std::runtime_error("easyfind: value not found");
	return (it);
}

template <typename T> typename T::const_iterator easyfind(const T &container,
	int value)
{
	typename T::const_iterator it = std::find(container.begin(),
			container.end(), value);
	if (it == container.end())
		throw std::runtime_error("easyfind: value not found");
	return (it);
}
